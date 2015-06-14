#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>
#include <site_types.h>

#define DEFAULT_RCVPORT "1999"
#define DEFAULT_MGROUP  "224.2.2.2"

#define LISTCHNID        0
#define CHNNR            200
#define MINCHNID         1
#define MAXCHNID         (MINCHNID + CHNNR - 1)

#define MSG_CHANNEL_MAX  (65536 - 20 - 8)
// #define MSG_CHANNEL_MAX  (512 - 20 - 8)
struct msg_channel_st{
    chnid_t id;  /* must between [MINCHNID,MAXCHNID] */
    uint8_t data[1];
} __attribute__((packed));


#define MSG_LIST_MAX     (65536 - 20 - 8)/*IP包大小-IP头-UDP头*/
struct msg_listentry_st{
    chnid_t id;
    uint16_t len;
    uint8_t descr[1];
} __attribute__((packed));

struct msg_list_st{
    chnid_t id;  /* must be LISTCHNID */
    struct msg_listentry_st entry[1];
} __attribute__((packed));

/* tcpdump -i eth1 -n */

#endif
