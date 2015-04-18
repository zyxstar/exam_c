#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include <netdb.h>

#include <stdio.h>

#define IP_SIZE 32

int main(void)
{
        struct addrinfo *res, *cur;
        int ret;
        char ip[IP_SIZE];

        ret = getaddrinfo("www.baidu.com", NULL, NULL, &res);
        //ret = getaddrinfo("www.chinaunix.net", NULL, NULL, &res);
        if (ret) {
                perror("getaddrinfo()");
                return 1;
        }

        printf("AF_INET = %d\n", AF_INET);
        printf("AF_INET6 = %d\n", AF_INET6);
        printf("SOCK_STREAM = %d\n", SOCK_STREAM);
        printf("SOCK_DGRAM = %d\n", SOCK_DGRAM);
        printf("SOCK_SEQPACKET = %d\n", SOCK_SEQPACKET);
        printf("IPPROTO_TCP = %d\n", IPPROTO_TCP);
        printf("IPPROTO_UDP = %d\n", IPPROTO_UDP);
        for (cur = res; cur != NULL; cur = cur->ai_next) {
                inet_ntop(AF_INET, &((struct sockaddr_in *)cur->ai_addr)->sin_addr, ip, IP_SIZE);
                printf("ai_family: %d, ai_socktype: %d, ai_protocol: %d, ip: %s\n", cur->ai_family, cur->ai_socktype, cur->ai_protocol, ip);
        }

        freeaddrinfo(res);

        return 0;
}
