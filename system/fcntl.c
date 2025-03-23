#include <fcntl.h>

/*
    int fcntl(int fd, int cmd, ... /* arg */);
        F_DUPFD
        F_GETFD
        F_SETFD
        F_GETFL
        F_SETFL
            O_APPEND
            O_NONBLOCK
            O_ASYNC
            O_DIRECT
            O_NOATIME
        F_GETOWN
        F_SETOWN
*/