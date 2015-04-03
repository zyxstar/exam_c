#include <sys/uio.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 4096
int main(int argc, char *argv[])
{
    char buf1[BUFSIZE];
    char buf2[BUFSIZE];
    struct iovec iov[2];
    int fd1, fd2;
    ssize_t size1, size2, size3;

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);

    size1 = read(fd1, buf1, BUFSIZE);
    printf("\033[31m%s size is: %d\033[0m\n", argv[1], size1);
    size2 = read(fd2, buf2, BUFSIZE);
    printf("\033[31m%s size is: %d\033[0m\n", argv[2], size2);

    iov[0].iov_base = buf1;
    iov[0].iov_len = size1;
    iov[1].iov_base = buf2;
    iov[1].iov_len = size2;

    size3 = writev(1, iov, 2);
    printf("\033[31mtotal size is: %d\033[0m\n", size3);

    close(fd1);
    close(fd2);

    return 0;
}
