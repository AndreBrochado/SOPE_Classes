// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define STDERR 2
#define NUMITER 1000
void * thrfunc(void * arg)
{
    int i;
    int* intArg = (int*) arg;
    fprintf(stderr, "Starting thread %d\n", intArg[0]);
    char str[5];
    sprintf(str, "%d", intArg[1]);
    for (i = 1; i <= NUMITER; i++) write(STDERR,str,strlen(str));
    return NULL;
}
int main()
{
    pthread_t ta, tb;
    int thr1Arg[] = {1, 42};
    int thr2Arg[] = {1, 52};
    pthread_create(&ta, NULL, thrfunc, &thr1Arg);
    pthread_create(&tb, NULL, thrfunc, &thr2Arg);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}
