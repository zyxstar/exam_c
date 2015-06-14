#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
#include <syslog.h>

#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>

#include <proto.h>
#include <server_conf.h>
#include <medialib.h>


struct server_conf_st server_conf = {
    .rcvport = DEFAULT_RCVPORT,
    .mgroup = DEFAULT_MGROUP,
    .ifname = DEFAULT_IF,
    .media_dir = DEFAULT_MEDIADIR,
    .runmode = run_daemon
};

int serversd;
struct sockaddr_in sndaddr;

static struct mlib_listentry_st *list;
static int list_size;

static void daemon_exit(int s){
    // thr_channel_destroyall();
    // thr_list_destroy();
    mlib_freechnlist(list);
    if(s < 0){
        syslog(LOG_ERR, "Daemon failure exit.");
        closelog();
        exit(1);
    }
    syslog(LOG_INFO, "Signal-%d caught, exit now.", s);
    closelog();
    exit(0);
}

static void printhelp(void){

}

static void daemonize(void){
    int fd;
    pid_t pid;
    pid = fork();
    if(pid > 0){
        exit(0);
    }
    fd = open("/dev/null", O_RDWR);
    if(fd < 0){
        syslog(LOG_ERR, "open() %s", strerror(errno));
        exit(1);
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if(fd > 2) close(fd);
    setsid();
    syslog(LOG_INFO, "Daemon initialized OK.");
    chdir("/");
    umask(0);
    return;
}

static int socket_init(void){
    struct ip_mreqn mreq;
    serversd = socket(AF_INET, SOCK_DGRAM, 0);
    if(serversd < 0){
        syslog(LOG_ERR, "socket(): %s", strerror(errno));
        exit(1);
    }
    inet_pton(AF_INET, server_conf.mgroup, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex(server_conf.ifname);
    if(setsockopt(serversd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0){
        syslog(LOG_ERR, "setsockopt(): %s", strerror(errno));
        exit(1);
    }

    sndaddr.sin_family = AF_INET;
    sndaddr.sin_port = htons(atoi(server_conf.rcvport));
    inet_pton(AF_INET, server_conf.mgroup, &sndaddr.sin_addr);
}


/*
 * -M mgroup
 * -P rcvport
 * -D media dir
 * -I NIC name
 * -F run foreground
 * -H help
 */

int main(int argc, char **argv){
    int err, c, i;

    signal(SIGTERM, daemon_exit);
    signal(SIGINT, daemon_exit);
    signal(SIGQUIT, daemon_exit);

    openlog("netradio", LOG_PID|LOG_PERROR, LOG_DAEMON);

    while(1){
        c = getopt(argc, argv, "P:M:D:I:FH");
        if( c < 0){
            break;
        }
        switch(c){
            case 'P':
                server_conf.rcvport = optarg;
                break;
            case 'M':
                server_conf.mgroup = optarg;
                break;
            case 'D':
                server_conf.media_dir = optarg;
                break;
            case 'I':
                server_conf.ifname = optarg;
                break;
            case 'F':
                server_conf.runmode = run_foreground;
                break;
            case 'H':
                printhelp();
                exit(0);
            default:
                abort();
        }
    }

    if(server_conf.runmode == run_daemon){
        daemonize();
    }

    socket_init();

    err = mlib_getchnlist(&list, &list_size);
    if(err){
        syslog(LOG_ERR, "mlib_getchnlist() : %s", strerror(err));
        exit(1);
    }
    syslog(LOG_DEBUG, "mlib_getchnlist() %d", list_size);

#if 0
    for(i = 0; i < list_size; i++){
        printf("CHN: %d %s\n", list[i].id, list[i].desc);
    }
#endif

    thr_list_create(list, list_size);
    for(i = 0; i < list_size; ++i){
        thr_channel_create(list + i);
        syslog(LOG_DEBUG, "thr_channel_create() %d", i);
    }

    while(1) pause();

    exit(0);

}
