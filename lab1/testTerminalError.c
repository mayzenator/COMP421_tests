// Tests error handling

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <terminals.h>
#include "../include/terminals.h"


char string[];
int length = 4;

char string1[] = "abcdefghijklmnopqrstuvwxyz\n";
int length1 = sizeof(string1) - 1;

int
main(int argc, char **argv)
{
    InitTerminalDriver();
    printf("You should get an error bc terminal 1 has not been initialized\n");
    ReadTerminal(1, string, length);
    printf("\n");
    InitTerminal(1);
    printf("You should get an error bc terminal 0 has not been initialized\n");
    ReadTerminal(0, string, length);
    printf("\n");
    printf("You should get an error bc terminal -1 is not a valid terminal number\n");
    WriteTerminal(-1, string1, length1);
    printf("\n");
    printf("You should get an error bc terminal 1 has already been initialized\n");
    InitTerminal(1);
    printf("\n");
    printf("You should get an error bc device driver has already been initialized\n");
    InitTerminalDriver();
    exit(0);
}