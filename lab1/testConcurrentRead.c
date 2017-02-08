// Tests parallel reads to the same terminal. They should not overlap.
// Also check to make sure if you "take" a newline in a previous readterminal, that future readterminals
// acknowledge that there is one less newline in the input buffer.

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <hardware.h>
#include <unistd.h>

void reader(void *);
void reader2(void *);
void reader3(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Begin three reader threads. These should read one after another. They should not be interleaved\n");
    printf("Type something like a\\nbbbbcccc\\n\n");
    fflush(stdout);
    sleep(10);
    ThreadCreate(reader, NULL);
    ThreadCreate(reader2, NULL);
    ThreadCreate(reader3, NULL);
    ThreadWaitAll();

    exit(0);
}

void
reader(void *arg)
{
    int status;

    printf("Doing ReadTerminal... \n");
    fflush(stdout);
    char string[2];
    int length = 2;
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}

void
reader2(void *arg)
{
    int status;

    printf("Doing ReadTerminal... \n");
    fflush(stdout);
    char string[4];
    int length = 4;
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}

void
reader3(void *arg)
{
    int status;

    printf("Doing ReadTerminal... \n");
    fflush(stdout);
    char string[3];
    int length = 3;
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}