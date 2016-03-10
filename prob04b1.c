#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//First approach: Get the PID from the UPStart process (saved on the UPSTART_SESSION environment variable)
//and wait until the parent of the son is the upstart instead of its parent == its parent has finished
int main(int argc, char* argv[], char* endp[]){
    pid_t pid = fork();
    
    if(pid == 0){
	int i = 0;
	
	while(strstr(endp[i], "UPSTART_SESSION=") == NULL)
		i++;
	char* upstartPidStr = malloc(sizeof(char)*10);
	upstartPidStr = (strrchr(endp[i], '/'));
	//remove the '/' from the string
	upstartPidStr++;
	int upstartPid = atoi(upstartPidStr);
	while(getppid() != upstartPid){} // could do to debug printf("%d != %d \n", getppid(), upstartPid);
	write(STDOUT_FILENO, "world !\n", strlen("world !\n"));
    }
    else{
	write(STDOUT_FILENO, "Hello ", strlen("Hello "));
        
    }
    return 0;
}
