#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 80

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
//    printf("Hello world!\n");
    int fd = STDIN_FILENO;
    int shouldClose = 0;

    if (argc > 1){
      fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("Failed to open file");
            return 1;
        }
        shouldClose = 1;
    } else {
           fd = open("redirect_fd1.txt", O_RDONLY);
           }

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE))){ // 0 std inp
    write(STDOUT_FILENO, buffer, bytes_read); // 1 std outp
    }

    if (bytes_read == -1) {
        perror("Read error");
    }

    if (shouldClose) {
        close(fd);
    }

    return 0;
}

