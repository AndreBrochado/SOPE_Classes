#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
 

//Second aproach: Parent process saves its pid, and son will wait until parent id is different from the initial (when it changes to upstart)
int main(){
    pid_t parentPid = getpid();
    
    if(fork() > 0){
        write(STDOUT_FILENO, "Hello ", strlen("Hello "));
    }
    else{
        while(getppid() == parentPid) {} //could have printf("%d == %d\n", getppid(), parentPid); for debugging
        write(STDOUT_FILENO, "world !\n", strlen("world !\n"));
    }
    return 0;
}

