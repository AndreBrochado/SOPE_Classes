#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#define INVALID 42
#define INTEGER 43
#define FLOAT 44

typedef struct{
    int resultCase;
    int resultInt;
    float resultFloat;
} DivRes;

int main(){
    int a[2];
    int fReq, fAns;
    do {
        fReq=open("/tmp/fifo_req",O_WRONLY);
        if (fReq==-1) sleep(1);
    } while (fReq==-1);
    
    do {
        fAns=open("/tmp/fifo_ans",O_RDONLY);
        if (fAns==-1) sleep(1);
    } while (fAns==-1);
    
    while(1){
    
        printf("x y ? "); scanf("%d %d",&a[0],&a[1]);
        write(fReq, a, 2*sizeof(int));
        DivRes result;
        int n = read(fAns, &result, sizeof(DivRes));
        if(n == 0)
            return 0;
        if(result.resultCase == INVALID)
            printf("Invalid Division!\n");
        else if(result.resultCase == INTEGER)
            printf("Integer Division: %d\n", result.resultInt);
        else
            printf("Float Division: %f\n", result.resultFloat);
    }
    return 0;
}
