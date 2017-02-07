// Tests parallel writes to different terminals. They should be able to run at the same time

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <hardware.h>

void writer(void *);
void writer2(void *);
void writer3(void *);

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    InitTerminal(2);
    InitTerminal(3);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    printf("Begin three writer threads. These should all output at the same time\n");
    ThreadCreate(writer, NULL);
    ThreadCreate(writer2, NULL);
    ThreadCreate(writer3, NULL);
    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    char string[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    int length = sizeof(string) - 1;
    status = WriteTerminal(2, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer2(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    int length = sizeof(string) - 1;
    status = WriteTerminal(3, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

void
writer3(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    char string[] = "--------------------------------------------------------------------------------------------------";
    int length = sizeof(string) - 1;
    status = WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}

