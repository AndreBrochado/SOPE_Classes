// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void sigint_handler(int signo)
{
    printf("In SIGINT handler ...\n");
}

int main(void)
{
    if (signal(SIGINT,sigint_handler) < 0) // = with SIGUSR1
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    int sleepTime = 30;
    while(sleepTime > 0){
    printf("Sleeping for %d seconds ...\n", sleepTime);
    sleepTime = sleep(sleepTime);
    printf("Waking up ...\n");
    }
    exit(0);
}

