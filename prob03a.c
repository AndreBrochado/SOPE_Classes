#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    int file, nr, nw;
    unsigned char buffer[BUFFER_SIZE];
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }
    file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror(argv[1]);
        return 2;
    }
    while ((nr = read(file, buffer, BUFFER_SIZE)) > 0)
        if ((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw != nr) { //write(.., .., nr) so it won't write more characters than it read
            close(file);
            return 4;
       } 
    close(file);
    return 0;
}
