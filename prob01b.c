#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

typedef struct{
    int num1, num2;    
} Nums;

int main(void)
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if (pid >0) //pai
    {
        Nums nums; 
        printf("PARENT:\n");
        printf("x y ? "); scanf("%d %d",&nums.num1,&nums.num2);
        close(fd[READ]);
        write(fd[WRITE],&nums,sizeof(Nums));
        close(fd[WRITE]);
    }
    else //filho
    {
        Nums nums2;
        //printf("SON:\n");
        close(fd[WRITE]);
        read(fd[READ],&nums2,sizeof(Nums));
        printf("SON:\n"); //WHY HERE AND NOT ABOVE ...?! - Because this printf waits for read (which waits for write, which waits for the scanf input), while the other doesn't
        printf("x + y = %d\n", nums2.num1 + nums2.num2);
        close(fd[READ]);
    }
    return 0;
}

