#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
char* name = (char*) malloc(sizeof(char)*100);
if(argc > 1){
	sprintf(name, "%s", argv[1]);
	int i;
	int number;
	for(i = 2; i < argc; i++){
		if(i == argc - 1)
			number = atoi(argv[i]);
		else
			sprintf(name, "%s %s", name, argv[i]);
}
	for(i = 0; i < number; i++)
	printf("Hello %s!\n", name);
}
else
printf("Hello!\n");
return 0;
}

