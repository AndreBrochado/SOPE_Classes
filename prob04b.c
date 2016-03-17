#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int i, n, status;
    for (i=1; i<=3; i++) {
        pid=fork();
        if (pid == 0){
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
            sleep(i*7); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
            exit(0);
        }
    }
    int j = 0;
    for (i=1 ;i<=4; i++ ) {
        printf("PARENT: working hard (task no. %d) ...\n",i);
        n=20; while((n=sleep(n))!=0);
        printf("PARENT: end of task no. %d\n",i);
	do{
        printf("PARENT: waiting for child no. %d ...\n",j);
        pid=waitpid(-1,&status,WNOHANG);
	i++;
	j++;
	}while(pid != 0);
        if (pid != -1 && pid != 0)
            printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
    }
    exit(0);
}

//execution note:
//on CTRL+C, program is interrupted and all its children too.
//on sending sigint: only kills the given process
