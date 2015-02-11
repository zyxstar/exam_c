// int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

char *client(char *ip, int port, int message_len){
    int serv_sock;
    if((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        error_handling("socket() error");

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    if(connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    char *message = calloc(1, message_len);
    int str_len;
    if((str_len= read(serv_sock, message, message_len-1)) == -1)
        error_handling("read() error");

    close(serv_sock);

    return message;
}

int main(){
    char *message = client("127.0.0.1", 5678, 30);
    printf("%d : %s\n", strlen(message), message);
    free(message);
    return 0;
}
