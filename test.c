#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[], char* endp[])
{
int i = 0;
while(endp[i] != NULL){
printf("%s\n", endp[i]);
i++;
}
return 0;
}
