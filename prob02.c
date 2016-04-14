#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

#define INVALID 42
#define INTEGER 43
#define FLOAT 44

typedef struct{
    int resultCase;
    int resultInt;
    float resultFloat;
} DivRes;

int main(void)
{
    int fd[2], rfd[2];
    pid_t pid;
    pipe(fd);
    pipe(rfd);
    pid = fork();
    if (pid >0) //pai
    {
        int a[2];
        //printf("PARENT:\n");
        printf("x y ? "); scanf("%d %d",&a[0],&a[1]);
        close(fd[READ]);
        close(rfd[WRITE]);
        write(fd[WRITE],a,2*sizeof(int));
        close(fd[WRITE]);
        DivRes result;
        read(rfd[READ], &result, sizeof(DivRes));
        if(result.resultCase == INVALID)
            printf("Invalid Division!\n");
        else if(result.resultCase == INTEGER)
            printf("Integer Division: %d\n", result.resultInt);
        else
            printf("Float Division: %f\n", result.resultFloat);
        close(rfd[READ]);
    }
    else //filho
    {
        int b[2];
        DivRes result; //IN THIS CASE COULD HAVE 1 WRITE FOR CASE AND 1 FOR RESULT, BUT WHEN THERE ARE MORE PROCESSES THAT COULD BE MESSY
        //printf("SON:\n");
        close(fd[WRITE]);
        close(rfd[READ]);
        read(fd[READ],b,2*sizeof(int));
        close(fd[READ]);
        //printf("SON:\n"); //WHY HERE AND NOT ABOVE ...?! - Because this printf waits for read (which waits for write, which waits for the scanf input), while the other doesn't
        //printf("x + y = %d\n", b[0]+b[1]);
        if(b[1] == 0)
            result.resultCase = INVALID;
        else if(b[0] % b[1] == 0){
            result.resultCase = INTEGER;
            result.resultInt = b[0]/b[1];
        }
        else {
            result.resultCase = FLOAT;
            result.resultFloat = (float) b[0]/b[1];
        }
        write(rfd[WRITE], &result, sizeof(DivRes));
        close(rfd[WRITE]);
    }
    return 0;
}

