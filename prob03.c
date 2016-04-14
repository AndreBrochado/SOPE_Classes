#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1
#define MAXLINE 1000

int main(int argc, char* argv[])
{
    if (argc != 2) { printf("usage: %s filename\n",argv[0]); exit(1); }
    
    int inputFile;
    
    if ((inputFile = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr,"can't open %s", argv[1]); exit(1);
    }

    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid >0) //pai
    {
        char line[MAXLINE];
        int nr;
        close(fd[READ]);
        while ((nr = read(inputFile, line, MAXLINE)) > 0)
            write(fd[WRITE],line,nr);
        close(fd[WRITE]);

    }
    else //filho
    {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        execlp("sort", "sort", NULL);
    }
    return 0;
}

