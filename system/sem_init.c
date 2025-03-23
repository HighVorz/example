#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    sem_init(&sem, 0, 0)
        0 线程共享, 非0 进程共享
        0 信号量初始值

    sem_wait(&sem)
        sem 为 0 时 阻塞
        非0 返回并 sem --

    sem_post(&sem)
        sem++; sem_wait 线程被唤醒
*/

// 定义信号量
sem_t sem;

// 线程 1 的函数
void*
thread1_func(void* arg) {
    printf("Thread 1: Waiting for signal...\n");
    sem_wait(&sem);  // 等待信号量
    printf("Thread 1: Received signal!\n");
    return NULL;
}

// 线程 2 的函数
void*
thread2_func(void* arg) {
    printf("Thread 2: Doing some work...\n");
    sleep(2);  // 模拟工作
    printf("Thread 2: Sending signal...\n");
    sem_post(&sem);  // 发送信号量
    return NULL;
}

int
main() {
    pthread_t thread1, thread2;

    // 初始化信号量
    if (sem_init(&sem, 0, 0) == -1) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    // 创建线程 1
    if (pthread_create(&thread1, NULL, thread1_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 创建线程 2
    if (pthread_create(&thread2, NULL, thread2_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 销毁信号量
    sem_destroy(&sem);

    printf("Main: All threads completed.\n");
    return 0;
}