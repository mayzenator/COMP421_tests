// HOW TO USE:
// Test to make character processing is not interrupted. That is, if write terminal is outputting '\r\n', the user should
// not be able to echo between the return and the newline

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void writer(void *);

char string[] = "--\r\n--\r\n--\r\n";
int length = sizeof(string) - 1;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    HardwareOutputSpeed(1, 1000);
    HardwareInputSpeed(1, 1);

    ThreadCreate(writer, NULL);
    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    printf("Doing WriteTerminal... '");
    printf("You should try to type between the \\r and the \\n. Your char should not be echoed until after the \\n\n");
    fflush(stdout);
    WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", length);
    fflush(stdout);
}