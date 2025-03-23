#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int
main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* filepath = argv[1];

    // 打开文件
    int fd = open(filepath, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Trying to lock the file...\n");

    // 加锁（独占锁）
    if (flock(fd, LOCK_EX) == -1) {
        perror("flock LOCK_EX");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File locked. Press Enter to unlock...\n");
    getchar();  // 等待用户输入

    // 解锁
    if (flock(fd, LOCK_UN) == -1) {
        perror("flock LOCK_UN");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File unlocked.\n");

    close(fd);
    return 0;
}