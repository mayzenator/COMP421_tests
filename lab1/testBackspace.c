// Tests to make sure you don't delete when the next char in the input buffer is a newline
// also checks to make sure that if you're not deleting from input buffer, you're also not deleting from echo buf

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

char string[];
int length = 4;


int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Type 'abcdef\\na' into terminal\n");
    printf("Press delete 5 times\n");
    sleep(10);
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
    printf("Expected: abcd\n");
    printf("Actual: %s\n", string);
    fflush(stdout);
}