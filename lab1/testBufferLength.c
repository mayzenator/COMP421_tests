// Tests whether or not you properly handle exceeded buffer length stuff
// When the input buffer is full, you should drop anything not already added.
// If the input buffer is full, you should also NOT echo the characters that are dropped.
// If the output buffer is full, your program should stall until space is available

// HOW TO USE:
// set your buffer length to something small like 5
// type more characters than your buffer length allows



#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <unistd.h>

void reader(void *);

//char string[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
char string[];
int length = 10;
//int length = sizeof(string) - 1;

//char string1[] = "123456789\n";
//int length1 = sizeof(string1) - 1;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    HardwareOutputSpeed(1, 1000);
    HardwareInputSpeed(1, 1);

    printf("Set buffer length to 5\n");
//    printf("Write Terminal should stall until the output buffer is available\n");
//    WriteTerminal(1, string1, length1);
    printf("Type 10 characters in terminal, with no \\n before the 5th character\n");
    sleep(20);
    ThreadCreate(reader, NULL);
    ThreadWaitAll();


    exit(0);
}


void
reader(void *arg)
{
    printf("Doing ReadTerminal... '");
    fflush(stdout);
    printf("This should stall because there's no \\n in the input buffer\n");
    printf("Once you have confirmed that it stalled, you should delete until you get to the first 5 characters, and then type \\n so the program finishes\n");
    ReadTerminal(1, string, length);
    printf("Read in %s",string);
    fflush(stdout);
}