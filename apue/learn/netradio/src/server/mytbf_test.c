#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <mytbf.h>

#define BUFSIZE 1024

int main(){
    int fd;
    char buf[BUFSIZE];
    int len, pos, size, ret;
    mytbf_t *tbf;

    fd = open("/etc/services", O_RDONLY);
    if(fd < 0){
        perror("open()");
        exit(1);
    }

    tbf = mytbf_init(10, 1000);
    if(tbf == NULL){
        perror("mytbf_init()");
        exit(1);
    }

    while(1){
        size = mytbf_fetchtoken(tbf, BUFSIZE);
        len = read(fd, buf, size);
        if(len < 0){
            perror("read()");
        }
        else if(len == 0){
            break;
        }
        mytbf_returntoken(tbf, size - len);
        pos = 0;
        while(len > 0){
            ret = write(1, buf + pos, len);
            len -= ret;
            pos += ret;
        }
    }

    close(fd);
    return 0;
}
