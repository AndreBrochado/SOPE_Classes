#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int direction = 1;

void sigusr_handler(int signo)
{
    printf("Entering SIGUSR: %d handler ...\n", signo);
    if(signo = 10)
	direction = 1;
    else
	direction = -1;
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = sigusr_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGUSR1,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    if (sigaction(SIGUSR2, &action, NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGTERM handler\n");
        exit(1);
    }
    int v = 0;
    while(1){
        printf("%d\n", v);
        sleep(1);
        v += direction;
    }
    exit(0);
}
