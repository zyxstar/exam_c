#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>
#include <site_types.h>

#define DEFAULT_RCVPORT "1999"
#define DEFAULT_MGROUP  "224.2.2.2"

#define LISTCHNID        0
#define CHNNR            200
#define MINCHNID         1
#define MAXCHNID         (MINCHNID+CHNNR-1)

struct msg_channel_st{
    chnid id;  /* must between [MINCHNID,MAXCHNID] */
    uint8_t data[1];
} __attribute__((packed));



struct msg_listentry_st{
    chnid id;
    uint16_t len;
    uint8_t descr[1];
} __attribute__((packed));

struct msg_list_st{
    chnid id;  /* must be LISTCHNID */
    struct msg_listentry_st entry[1];
} __attribute__((packed));



#endif
