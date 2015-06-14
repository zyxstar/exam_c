#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <getopt.h>
#include <arpa/inet.h>

#include <proto.h>
#include <site_types.h>
#include <client_conf.h>


struct client_conf_st client_conf = {
    .rcvport = DEFAULT_RCVPORT,
    .mgroup = DEFAULT_MGROUP,
    .player_cmd = DEFAULT_PLAYERCMD
};


int main(){
    int i;
    int sd;
    struct msg_list_st *listbuf;
    struct msg_listentry_st *tmp;
    struct ip_mreqn mreq;
    struct sockaddr_in raddr;

    int id[3] = {12, 23, 34};
    char *descr[3] = {"Music", "Opera", "Talks"};

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0){
        perror("socket()");
        exit(1);
    }

    listbuf = malloc(28);
    if(listbuf == NULL){
        perror("malloc()");
        exit(1);
    }

    inet_pton(AF_INET, client_conf.mgroup, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex("eth1");
    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0){
        perror("setsockopt()");
        exit(1);
    }

    listbuf->id = LISTCHNID;
    tmp = listbuf->entry;
    for(i = 0; i < 3; i++ ){
        // printf("%p\n", tmp);
        tmp->id = id[i];
        tmp->len = htons(9);
        strncpy((char *)tmp->descr, descr[i], 6);
        // printf("%s\n", tmp->descr);
        tmp = (void *)(((char *)tmp) + 9);
    }

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(atoi(client_conf.rcvport));
    inet_pton(AF_INET, client_conf.mgroup, &raddr.sin_addr);
    while(1){
        sendto(sd, listbuf, 28, 0, (struct sockaddr *)&raddr, sizeof(raddr));
        sleep(1);
    }
}
