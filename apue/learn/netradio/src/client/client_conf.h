#ifndef CLIENT_CONF_H
#define CLIENT_CONF_H

struct client_conf_st{
    char *rcvport;
    char *mgroup;
    char *ifname;
    char *player_cmd;
};


extern struct client_conf_st client_conf;

/* - means read from stdin */
#define DEFAULT_PLAYERCMD  "/usr/bin/mpg123 - >/dev/null 2>&1"
#define DEFAULT_IF         "eth0"


#endif

/*
 default
 conf
 env
 cmd args
*/
