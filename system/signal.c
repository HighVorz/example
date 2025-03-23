#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    1   SIGHUP
    2   SIGINT
    3   SIGQUIT
    5   SIGTRAP
    6   SIGABRT
    9   SIGKILL     cannot ignore
    15  SIGTERM

*/

// 自定义信号处理函数
void
handle_signal(int signum) {
    if (signum == SIGINT) {
        printf("\nCaught SIGINT (Ctrl+C)! Exiting gracefully...\n");
        exit(EXIT_SUCCESS);
    }
}

int
main() {
    // 设置信号处理函数
    if (signal(SIGINT, handle_signal) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to trigger the signal handler.\n");

    // 无限循环，等待信号
    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}