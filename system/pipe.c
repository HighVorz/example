#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main() {
    int pipefd[2];  // pipefd[0] 用于读取，pipefd[1] 用于写入
    pid_t pid;

    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {        // 子进程
        close(pipefd[1]);  // 关闭写端

        char buffer[128];
        ssize_t count = read(pipefd[0], buffer, sizeof(buffer));  // 从管道读取数据
        if (count == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process received: %s\n", buffer);
        close(pipefd[0]);  // 关闭读端
    } else {               // 父进程
        close(pipefd[0]);  // 关闭读端

        const char* message = "Hello from parent process!";
        if (write(pipefd[1], message, strlen(message) + 1) == -1) {  // 向管道写入数据
            perror("write");
            exit(EXIT_FAILURE);
        }

        printf("Parent process sent: %s\n", message);
        close(pipefd[1]);  // 关闭写端
    }

    return 0;
}