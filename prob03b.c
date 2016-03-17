#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int direction = 1;

void sigusr_handler(int signo)
{
    //printf("Entering SIGUSR: %d handler ...\n", signo);
    if(signo == SIGUSR1)
	direction = 1;
    else if(signo == SIGUSR2)
	direction = -1;
}

int main(void)
{
    srand(time(NULL));
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
    int v = 0, numPrints = 0;
    int pid = fork();
    if(pid > 0){
        while(waitpid(-1, NULL, WNOHANG) == 0){
            int sig = rand() % 3;
            if(sig == 1)
                kill(pid, SIGUSR1);
            else if(sig == 2)
                kill(pid, SIGUSR2);
	    sleep(1);
        }
    }
    else{
        while(numPrints < 50){
            printf("%d\n", v);
            v += direction;
            numPrints++;
	    sleep(1);
        }
    }
    exit(0);
}
