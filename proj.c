/* LISTAR FICHEIROS REGULARES E SUB-DIRECTÓRIOS DE UM DIRECTÓRIO */
/* USO: listdir2 dirname */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

#define FILE_LIST_NAME "files.txt"
#define FILE_NAME_SIZE 50
#define PATH_SIZE 255

void writeInfoToFile(struct dirent* direntp, struct stat* statBuf, FILE* fileList, char* dirName){
    char* name = malloc(sizeof(char)*FILE_NAME_SIZE);
    char* path = malloc(sizeof(char)*PATH_SIZE);
    char* buf = malloc(sizeof(char)*PATH_SIZE);
    name = direntp->d_name;
    sprintf(path,"%s/%s/",getcwd(buf, PATH_SIZE), dirName);
    fprintf(fileList, "%s %zu %lld %s\n", name, statBuf->st_size, (long long) statBuf->st_mtim.tv_sec, path);
    free(name);
    free(path);
    free(buf);
}

int main(int argc, char *argv[])
{
    DIR *dirp;
    FILE *fileList;
    struct dirent *direntp;
    struct stat stat_buf;
    char name[200];
    int proccessCount = 0;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }
    if ((dirp = opendir(argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    if((fileList = fopen(FILE_LIST_NAME, "a")) == NULL){
        perror(FILE_LIST_NAME);
        exit(3);
    }
    while ((direntp = readdir(dirp)) != NULL)
    {
	char* buf = malloc(sizeof(char)*256);
        sprintf(name,"%s/%s/%s",getcwd(buf, 256), argv[1],direntp->d_name); // <----- NOTAR
	    //printf("%s\n", name);
	    
        // alternativa a chdir(); ex: anterior
        if (lstat(name, &stat_buf)==-1)
         // testar com stat()
            {
            perror("lstat ERROR");
            exit(3);
            }
        if (S_ISDIR(stat_buf.st_mode) && direntp->d_name != "." && direntp->d_name != ".."){
            /*createProccess(name);
            proccessCount++;*/
        }
        else if(S_ISREG(stat_buf.st_mode)){
            writeInfoToFile(direntp, stat_buf, fileList, argv[1]);
        }
        int pid=waitpid(-1, NULL,WNOHANG);
        if (pid != -1 && pid != 0)
            proccessCount--;
    }
    for(proccessCount; proccessCount > 0; proccessCount--) wait(NULL);
    closedir(dirp);
    exit(0);
}

