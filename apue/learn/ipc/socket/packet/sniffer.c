#include <sys/types.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1600

static void print_packet(FILE *fp, const unsigned char *buf, int len)
{
        int i;

        for (i = 0; i < len; i++) {
                fprintf(fp, "%02x ", buf[i]);
        }
        fprintf(fp, "\n\n");
        fflush(fp);
}

/* # ./a.out interface(device name) path(output file name) */
int main(int argc, char **argv)
{
        int sd;
        struct sockaddr_ll sll;
        int ret;
        struct packet_mreq mreq;
        int ifindex;
        FILE *fp;
        unsigned char buf[BUFSIZE];

        if (argc != 3) {
                fprintf(stderr, "argment...\n");
                return 1;
        }

        fp = fopen(argv[2], "a");
        if (fp == NULL) {
                perror(argv[2]);
                goto fopen_output_err;
        }

        sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
        if (sd == -1) {
                perror("socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))");
                goto socket_err;
        }

        ifindex = if_nametoindex(argv[1]);

        sll.sll_family = AF_PACKET;
        sll.sll_protocol = htons(ETH_P_ALL);
        sll.sll_ifindex = ifindex;
        ret = bind(sd, (struct sockaddr *)&sll, sizeof(sll));
        if (ret == -1) {
                perror("bind()");
                goto bind_err;
        }

        mreq.mr_ifindex = ifindex;
        mreq.mr_type = PACKET_MR_PROMISC;
        ret = setsockopt(sd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
        if (ret == -1) {
                perror("setsockopt(PACKET_MR_PROMISC)");
                goto setsockopt_PROMISC_err;
        }

        while (1) {
                ret = read(sd, buf, BUFSIZE);
                print_packet(fp, buf, ret);
        }

        close(sd);
        fclose(fp);

        return 0;






setsockopt_PROMISC_err:
bind_err:
        close(sd);
socket_err:
        fclose(fp);
fopen_output_err:
        return 1;
}
