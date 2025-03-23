#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>  // iovec
#include <unistd.h>   // include readv writev close

int
main() {
    char buf1[10] = {0};
    char buf2[20] = {0};
    char buf3[30] = {0};

    struct iovec iov[3];

    iov[0].iov_base = buf1;
    iov[0].iov_len = sizeof(buf1);

    iov[1].iov_base = buf2;
    iov[1].iov_len = sizeof(buf2);

    iov[2].iov_base = buf3;
    iov[2].iov_len = sizeof(buf3);

    int fd = open("input/iovec.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = readv(fd, iov, 3);
    if (bytes_read == -1) {
        perror("readv");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Total bytes read: %zd\n", bytes_read);

    printf("Buffer 1: %.*s\n", (int)iov[0].iov_len, (char*)iov[0].iov_base);
    printf("Buffer 2: %.*s\n", (int)iov[1].iov_len, (char*)iov[1].iov_base);
    printf("Buffer 3: %.*s\n", (int)iov[2].iov_len, (char*)iov[2].iov_base);

    close(fd);

    return 0;
}