// Tests example from document:
// HOW TO USE:
// type in the following line into terminal
// Hello\b\b\b\bi\nUniverse\b\b\b\b\b\b\b\bWorld\nGood bye

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(0);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Type \nHello\\b\\b\\b\\bi\\nUniverse\\b\\b\\b\\b\\b\\b\\b\\bWorld\\nGood bye\n");

    sleep(10);
    ThreadCreate(reader, NULL);
    ThreadWaitAll();

    exit(0);
}

void
reader(void *arg)
{
    printf("Doing ReadTerminal... \n");
    fflush(stdout);
    sleep(20);
    int len1, len2, len3;
    char buf1[2];
    char buf2[10];
    char buf3[10];
    char buf4[10];
    len1 = ReadTerminal(0, buf1, 2);
    printf("Expected: len1 = 2 buf1 = Hi\n");
    printf("Actual:   len1 = %d buf1 = %s\n", len1, buf1);
    len2 = ReadTerminal(0, buf2, 10);
    printf("Expected: len2 = 1 buf2 = \\n\n");
    printf("Actual:   len2 = %d buf2 = %s\n", len2, buf2);
    len3 = ReadTerminal(0, buf3, 10);
    printf("Expected: len3 = 6 buf3 = World\\n\n");
    printf("Actual:   len3 = %d buf3 = %s\n", len3, buf3);
    printf("Next read terminal should stall until \\n is typed\n");
    len1 = ReadTerminal(0, buf4, 10);
    fflush(stdout);
}
