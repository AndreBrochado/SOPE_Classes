#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

#define MAX_STRING_SIZE 100

int main(void)
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid >0) //pai
    {
        char a[2][MAX_STRING_SIZE];
        printf("PARENT:\n");
        printf("x y ? "); scanf("%s %s",a[0],a[1]);
        close(fd[READ]);
        write(fd[WRITE],a,2*MAX_STRING_SIZE);
        close(fd[WRITE]);
    }
    else //filho
    {
        char b[2][MAX_STRING_SIZE];
        //printf("SON:\n");
        close(fd[WRITE]);
        read(fd[READ],b,2*MAX_STRING_SIZE);
        /*int x, y;
        sscanf(b[1], "%d", x);
        sscanf(b[2], "%d", y);*/
        printf("SON:\n"); //WHY HERE AND NOT ABOVE ...?! - Because this printf waits for read (which waits for write, which waits for the scanf input), while the other doesn't
        printf("x + y = %d\n", atoi(b[0])+atoi(b[1]));
        close(fd[READ]);
    }
    return 0;
}

