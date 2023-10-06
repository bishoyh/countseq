#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }
    posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL

    char buffer[4000096];
    ssize_t bytesRead;
    int count = 0;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == '>') {
                count++;
            }
        }
    }

    if (bytesRead == -1) {
        perror("Error reading the file");
        close(fd);
        return 1;
    }

    printf("%d\n", count);

    close(fd);
    return 0;
}
