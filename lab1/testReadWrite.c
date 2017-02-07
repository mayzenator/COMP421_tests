// Concurrent read and write

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

char string[];
int length = 5;

void writer1(void *);

char string1[] = "abcdefghijklmnopqrstuvwxyz\n";
int length1 = sizeof(string1) - 1;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(reader, NULL);
    ThreadCreate(writer1, NULL);
    ThreadWaitAll();



    exit(0);
}

void
writer1(void *arg)
{
    int status;

    status = WriteTerminal(1, string1, length1);
    if (status != length1)
        fprintf(stderr, "Error: writer1 status = %d, length1 = %d\n",
                status, length1);
}

void
reader(void *arg)
{
    int status;

    printf("Doing ReadTerminal... '");
    fflush(stdout);
    sleep(5);
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}