#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <terminals.h>
#include <hardware.h>

void writer(void *, int);
void reader_blocking(void *);
void writer2(void *);
void writer1(void *);
void check_stats();

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    InitTerminal(2);

    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));

    ThreadCreate(reader_blocking, NULL);
    ThreadCreate(writer1, NULL);

    //Should immediately begin writing.  
    ThreadCreate(writer2, NULL);
    ThreadWaitAll();

    check_stats();    
    

    exit(0);
}


void
writer(void *dummy, int term)
{
    int i, j, n;
    int status;
    char buf[128];
    char *cp;
    int len;

    n = 0;
    int total_len = 0;
    for (i = 0; i < 10; i++)
    {
    	cp = buf;
    	for (j = 0; j < 5; j++)
    	{
    	    sprintf(cp, "%2d... ", (++n) * term);
    	    cp += strlen(cp);
    	}
    	strcpy(cp, "\n");
    	len = cp - buf + 1;
    	printf("%s\n", buf);
    	status = WriteTerminal(term, buf, len);
        total_len += status;
    	if (status != len)
    	    fprintf(stderr, "Error: writer status = %d, len = %d\n",
    		status, len);
    }
    printf("User_in should be: %i for Term %i\n", total_len, term);
}

void reader_blocking(void *dummy)
{
	int buflen = 1024;
	char buf[buflen];	
	
	ReadTerminal(1, buf, buflen);
	printf("Finished Reading\n"); 
}

void writer1(void *dummy)
{
    writer(dummy, 1);
    printf("Finished Writing term1\n");
}

void writer2(void *dummy)
{
    writer(dummy, 2);
    printf("Finished Writing term2\n");
}

void check_stats()
{

    struct termstat stats[NUM_TERMINALS];

    TerminalDriverStatistics(stats);

    printf("Received Stats:\n");
    int term = 0;
    while (term < NUM_TERMINALS)  {
        int tty_in = stats[term].tty_in;
        int tty_out = stats[term].tty_out;
        int user_in = stats[term].user_in;
        int user_out = stats[term].user_out;

        printf("Term %i: tty_in %i, tty_out %i, user_in %i, user_out %i\n",
        term, tty_in, tty_out, user_in, user_out);  
        term++;
    }

    printf("Expected Stats:\n");
    printf("Term 0: tty_in -1, tty_out -1, user_in -1, user_out -1\nTerm 1: tty_in X, tty_out 321 + X, user_in 310, user_out Y\nTerm 2: tty_in0, tty_out321, user_in311, user_out0\nTerm 3: tty_in -1, tty_out -1, user_in -1, user_out -1\n");
    printf("X and Y depend on what you typed into Terminal 1.\n");
}
