#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* filepath = argv[1];
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 获取文件大小
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }
    off_t file_size = sb.st_size;

    // 将文件映射到内存
    void* mapped = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 关闭文件描述符，不影响已映射的内存
    close(fd);

    // 打印文件内容
    printf("File content:\n%s\n", (char*)mapped);

    // 解除映射
    if (munmap(mapped, file_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    return 0;
}