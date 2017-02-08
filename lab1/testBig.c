// Big daddy test. This has 5 threads on the same terminal, writing and reading concurrently.
// You should check to make sure the reading does not block the writing.
// Also check to make sure a write to terminal 3 is occurring in parallel.

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <hardware.h>
#include <unistd.h>

void writer(void *);
void writer2(void *);
void writer3(void *);
void writer4(void *);
void reader(void *);
void reader2(void *);
void reader3(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    InitTerminal(3);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Begin typing stuff in terminal 1 to be read in by readterminal\n");
    sleep(10);
    printf("Begin reading and writing\n");
    ThreadCreate(writer4, NULL);
    ThreadCreate(reader, NULL);
    ThreadCreate(writer, NULL);
    ThreadCreate(writer2, NULL);
    ThreadCreate(reader2, NULL);
    ThreadCreate(writer3, NULL);

    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    int status;

    printf("Doing WriteTerminal... \n");
    fflush(stdout);
    char string[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    int length = sizeof(string) - 1;
    status = WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer2(void *arg)
{
    int status;

    printf("Doing WriteTerminal... \n");
    fflush(stdout);
    char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    int length = sizeof(string) - 1;
    status = WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer3(void *arg)
{
    int status;

    printf("Doing WriteTerminal... \n");
    fflush(stdout);
    char string[] = "--------------------------------------------------------------------------------------------------";
    int length = sizeof(string) - 1;
    status = WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer4(void *arg)
{
    int status;

    printf("Doing WriteTerminal... \n");
    fflush(stdout);
    char string[] = "--------------------------------------------------------------------------------------------------";
    int length = sizeof(string) - 1;
    status = WriteTerminal(3, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
reader(void *arg)
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
reader2(void *arg)
{
    int status;

    printf("Doing ReadTerminal... \n");
    fflush(stdout);
    char string[5];
    int length = 5;
    status = ReadTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    printf("Read in: %s\n", string);
    fflush(stdout);
}