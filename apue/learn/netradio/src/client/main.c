#include <stdio.h>
#include <proto.h>
#include <site_types.h>

static int pd[2];

struct client_conf_st client_conf = {
    .rcvport = DEFAULT_RCVPORT,
    .mgroup = DEFAULT_MGROUP,
    .player_cmd = DEFAULT_PLAYERCMD
};

static void printhelp(){

}




/*
 * -P --port 指定接收端口
 * -M --mgroup 指定多播组
 * -p --player 指定播放器命令行
 * -H --help 显示帮助
 */

struct option argarr[] = {
    {"port", 1, NULL, 'P'},
    {"mgroup", 1, NULL, 'M'},
    {"player", 1, NULL, 'p'},
    {"help", 0, NULL, 'H'},
};

#define NR_ARG  4

int main(int argc, char **argv){

    pid_t pid;
    int c;
    int sd;
    struct sockaddr_in laddr;

    while(1){
        c = getopt_long(argc, argv, "P:M:p:H", argarr, NR_ARG);
        if( c < 0){
            break;
        }
        switch(c){
            case 'P':
                client_conf.rcvport = optarg;
                break;
            case 'M':
                client_conf.mgroup = optarg;
                break;
            case 'p':
                client_conf.player_cmd = optarg;
                break;
            case 'H':
                printhelp();
                exit(0);
            default:
                abort();
        }
    }

    sd = socket(AF_INET, SOCK_DGRAM, 0);/*IPPROTO_UDP*/
    if(sd < 0){
        perror("socket()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(client_conf.rcvport));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);

    if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) < 0){
        perror("bind()");
        exit(1);
    }


    if(pipe(pd) < 0){
        perror("pipe()");
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        perror("fork()");
        exit(1);
    }
    if(pid == 0){
        close(pd[1]);
        dup2(pd[0], 0);
        if(pd[0] > 0){
            close(pd[0]);
        }
        /* skill: use shell to run cmd*/
        execl("/bin/sh", "sh", "-c", client_conf.player_cmd, NULL);
        exit(0);
    }
    close(pd[0]);


    while(1){
        /*收包*/
        if(is节目单){
            break;
        }
    }

    /*选择频道*/
    while(1){
        /*收包*/
        if(is选定频道){
            write(pd[1], )
        }
    }

    exit(0);
}
