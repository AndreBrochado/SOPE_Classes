#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    int file, nr, nw, save, destFile;
    unsigned char buffer[BUFFER_SIZE];
    if (argc != 2 && argc != 3) {
        printf("Usage: %s <source_file> [<destination_file]\n", argv[0]);
        return 1;
    }
    file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror(argv[1]);
        return 2;
    }
    if (argc == 3){
	destFile = open(argv[2], O_WRONLY | O_CREAT, 0644);
	save = dup(STDOUT_FILENO);
	dup2(destFile, STDOUT_FILENO);
    }
    while ((nr = read(file, buffer, BUFFER_SIZE)) > 0)
        if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) { //write(.., .., nr) so it won't write more characters than it read
            close(file);
            return 4;
    }
    if(argc == 3){
	dup2(save, STDOUT_FILENO);
	char test[] = "Done!\n";
	write(STDOUT_FILENO, &test, sizeof(test));
	close(destFile);
    }

    close(file);
    return 0;
}
