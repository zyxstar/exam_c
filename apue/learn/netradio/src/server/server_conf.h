#ifndef SERVER_CONF_H
#define SERVER_CONF_H

enum{
    run_daemon,
    run_foreground
};

struct server_conf_st{
    char *rcvport;
    char *mgroup;
    char *media_dir;
    char *ifname;
    int runmode;
};


extern struct server_conf_st server_conf;
extern int serversd;
extern struct sockaddr_in sndaddr;

#define DEFAULT_MEDIADIR  "/var/media"
#define DEFAULT_IF        "eth1"

#endif
