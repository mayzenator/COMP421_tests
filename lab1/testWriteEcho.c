// HOW TO USE:
// Test to make sure echo gets priority over write. Just start typing while write terminal is printing a's

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void writer(void *);

char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
int length = sizeof(string) - 1;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(writer, NULL);
    sleep(20);
    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    printf("Doing WriteTerminal... '");
    fflush(stdout);
    WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", length);
    fflush(stdout);
}