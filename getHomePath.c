#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* endp[]){
    while(strstr(endp[i], "OLDPWD=") == NULL)
		i++;
	char* homePath = malloc(sizeof(char)*256);
	homePath = (strrchr(endp[i], '='));
	//remove the '=' from the string
	homePath++;
    return 0;
}
