#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sigint_handler(int signo)
{
    printf("Entering SIGINT handler ...\n");
    int n=10;
    while((n=sleep(n))!=0){printf("sleeping %d\n", n);}; //problem stops sigint handler to execute sigterm handler then continues sigint handler
    printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo)
{
    printf("SIGTERM handler, signo: %d ...\n", signo);
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGINT,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    action.sa_handler = sigterm_handler;
    if (sigaction(SIGTERM, &action, NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGTERM handler\n");
        exit(1);
    }
    printf("Try me with CTRL-C ...\n");
    while(1) pause();
    exit(0);
}
