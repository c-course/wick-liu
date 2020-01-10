#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char buf;
    int fd = open("../out.txt", O_RDWR);
    int wd = open("../in.txt", O_WRONLY | O_CREAT, S_IRWXU);

    if (fd < 0) {
        return fd;
    }

    if (wd < 0) {
        return wd;
    }

    while (read(fd, &buf, 1) > 0) {
        write(wd, &buf, 1);
    }

    return 0;
}