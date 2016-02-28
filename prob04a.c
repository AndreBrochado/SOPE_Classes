#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
char* name = (char*) malloc(sizeof(char)*100);
if(argc > 1){
sprintf(name, "%s", argv[1]);
int i;
for(i = 2; i < argc; i++)
sprintf(name, "%s %s", name, argv[i]);
}
printf("Hello %s!\n", name);
return 0;
}

