// Basic read terminal

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

char string[5];
int length = 5;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

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
    sleep(10);
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}