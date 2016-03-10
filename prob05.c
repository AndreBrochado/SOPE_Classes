#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
 
int main(){
    
    
    if(fork() > 0){ //parent, prints last word
        wait(NULL);
        write(STDOUT_FILENO, "friends\n", strlen("friends\n"));
    }
    else{ //son, needs to create grandson
        if(fork() > 0){ // son, prints second word
            wait(NULL);
            write(STDOUT_FILENO, " my ", strlen(" my "));
        }
        else
            write(STDOUT_FILENO, "Hello", strlen("Hello"));
    }
    return 0;
}
