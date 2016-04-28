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
    char* charArg = (char*) arg;
    fprintf(stderr, "Starting thread %c\n", charArg[0]);
    for (i = 1; i <= NUMITER; i++) write(STDERR, &charArg[1],1);
    return NULL;
}
int main()
{
    pthread_t ta, tb;
    char thr1Arg[] = {'a', 'A'};
    char thr2Arg[] = {'b', 'B'};
    pthread_create(&ta, NULL, thrfunc, &thr1Arg);
    pthread_create(&tb, NULL, thrfunc, &thr2Arg);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    return 0;
}
