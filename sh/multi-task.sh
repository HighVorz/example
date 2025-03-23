#!/bin/sh

# 定义一个函数
task() {
    echo "Task $1 started"
    sleep 3  # 模拟耗时任务
    echo "Task $1 finished"
}

# 启动多个任务
task 1 &
task 2 &
task 3 &

# 等待所有后台任务完成
wait

echo "All tasks completed"

# valgrind
# asan
# tsan