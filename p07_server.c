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
    int fReq, fAns;
    int b[2];
    DivRes result;
    mkfifo("/tmp/fifo_ans", 0777);
    mkfifo("/tmp/fifo_req", 0777);
    fReq = open("/tmp/fifo_req", O_RDONLY);
    fAns = open("/tmp/fifo_ans", O_WRONLY);
    while(1){
        
        read(fReq,b,2*sizeof(int));
    
        if(b[0] == 0 && b[1] == 0)
            break;
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
        write(fAns, &result, sizeof(DivRes));
    }
    close(fReq);
    close(fAns);
    return 0;
}
