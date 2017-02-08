#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <terminals.h>
#include <hardware.h>
#include <unistd.h>

void writer(void *);
void reader(void *);

char string1[] = "abcdefghijklmnopqrstuvwxyz\n";
int length1 = sizeof(string1) - 1;

char string2[] = "0123456789\n";
int length2 = sizeof(string2) - 1;

char string3[] = "suhhhhhhhhhhduuuudeeee\n";
int length3 = sizeof(string3) - 1;
int
main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(writer, NULL);
    ThreadCreate(reader, NULL);
    ThreadWaitAll();
    struct termstat *stats = calloc(NUM_TERMINALS, sizeof(struct termstat *));
    int i = 0;
    for (; i < NUM_TERMINALS; i++) {
        //stats[i] = {.tty_in = -2, .tty_out = -2, .user_in -2, .user_out = -2};
        struct termstat stat = {-2, -2, -2, -2};

        stats[i] = stat;
    }
    int status = TerminalDriverStatistics(stats);
    fprintf(stdout, "status of statistics: %d\n", status);
    fprintf(stdout, "tty_in of struct 1: %d\n", stats[1].tty_in);
    for (i = 0; i < NUM_TERMINALS; i++) {
        fprintf(stdout, "Struct %d: \n\ttty_in: %d\n\ttty_out: %d\n\tuser_out: %d\n\tuser_in: %d\n", i, stats[i].tty_in, stats[i].tty_out, stats[i].user_in, stats[i].user_out);
    }
    //fprintf(stdout, "user_out of struct 1: %d\n", stats[1].user_out);
    //fprintf(stdout, "user_out of struct 2: %d\n", stats[2].user_out);
    //fprintf(stdout, "user_out of struct 0: %d\n", stats[0].user_out);
    sleep(100);
    exit(0);
}

void
writer(void *arg)
{
    int status;

    status = WriteTerminal(1, string1, length1);
    if (status != length1)
        fprintf(stderr, "Error: writer1 status = %d, length1 = %d\n",
                status, length1);
    printf("WriteTerminal returned! status: %d\n", status);
    return;
}

void
reader(void *arg)
{
    int status;
    char* buffer = malloc(sizeof(char) * length2);
    status = ReadTerminal(1, buffer, length2);
    printf("Read Terminal took in %d chars\n", status);
    printf("Read Terminal read '%s'\n", buffer);
    fflush(stdout);
    return;
}
