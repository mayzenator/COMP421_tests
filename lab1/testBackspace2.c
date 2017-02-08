// Test to again make sure input buffer characters aren't deleted if newline is the last character

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

char string[10];
int length = 10;


int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Type '1234\\n\\b\\b' into terminal\n");
    sleep(10);
    printf("Calling read terminal should not be blocked because you shouldn't have deleted the newline");
    ThreadCreate(reader, NULL);
    ThreadWaitAll();

    exit(0);
}

void
reader(void *arg)
{
    int status;

    printf("Doing ReadTerminal... '");
    fflush(stdout);
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Expected: 1234\n");
    printf("Actual: %s\n", string);
    fflush(stdout);
}
