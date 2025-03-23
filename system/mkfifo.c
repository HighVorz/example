#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
    mkfifo("fifo_file", mode)

    mode
        0666  all user can read and write
        0644  owner can read and write, other can read only

    EEXIST
    ENOENT
    EACCES

    writer process
        int fd = open("my_fifo", O_WRONLY);
    reader
        int fd = open("my_fifo", O_RDONLY);

*/