#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
    int status;
    pid_t pid = fork();
    
    if(pid > 0){
	wait(&status);
        write(STDOUT_FILENO, "world !\n", strlen("world !\n"));
    }
    else{
        write(STDOUT_FILENO, "Hello ", strlen("Hello "));
    }
    return 0;
}
