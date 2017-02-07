// Tests error handling for bad parameters

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <terminals.h>
#include "../include/terminals.h"

char string[];

int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    printf("You should get an error bc the buffer is null.\n");
    ReadTerminal(1, NULL, 5);
    printf("You should get an error bc buflen is negative.\n");
    WriteTerminal(1, string, -1);
    exit(0);
}