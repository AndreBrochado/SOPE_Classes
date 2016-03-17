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
    //prepare sigaction
    struct sigaction action;
    action.sa_handler = sigint_handler;
    //sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT,&action,NULL) < 0) // = with SIGUSR1
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

