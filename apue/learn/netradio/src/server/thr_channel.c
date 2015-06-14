#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <syslog.h>
#include <sched.h>

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include <site_types.h>
#include <proto.h>
#include <server_conf.h>
#include <thr_channel.h>
#include <medialib.h>

#define BUFSIZE 1024

struct thr_channel_ent_st{
    chnid_t chnid;
    pthread_t tid;
};

static struct msg_channel_st *sbuf;
static struct thr_channel_ent_st thr_channel[CHNNR];
static int tid_nextpos = 0;

static void *thr_channel_snder(void *ptr){
    struct mlib_listentry_st *ent = ptr;
    char buf[BUFSIZE];
    int len, ret;
    struct msg_channel_st *sbufp;
    int datasize;

    syslog(LOG_DEBUG, "thr_channel_snder is working channel %d", ent->id);

    sbufp = malloc(MSG_CHANNEL_MAX);
    if(sbufp == NULL){
        syslog(LOG_ERR, "malloc(): %s", strerror(errno));
        exit(1);
    }

    datasize = MSG_CHANNEL_MAX - sizeof(chnid_t);

    sbufp->id = ent->id;
    while(1){
        pthread_testcancel();//设置cancel点，方便将来能够被cancel
        len = mlib_readchn(ent->id, sbufp->data, datasize);

        sendto(serversd, sbufp, len + sizeof(chnid_t), 0, (void *)&sndaddr, sizeof(sndaddr));
        sched_yield();//yield the processor
        // ret = write(1, buf, len);
        // fprintf(stderr, "%d bytes sent.\n", ret);
    }
}

int thr_channel_create(struct mlib_listentry_st *ptr){
    int len, err;

    sbuf = malloc(MSG_CHANNEL_MAX);
    if(sbuf == NULL){
        syslog(LOG_ERR, "malloc(): %s", strerror(errno));
        //daemon_exit(-1);
        return -ENOMEM;
    }

    if(tid_nextpos >= CHNNR){
        free(sbuf);
        return -ENOSPC;
    }

    err = pthread_create(&thr_channel[tid_nextpos].tid, NULL, thr_channel_snder, ptr);
    if(err){
        syslog(LOG_WARNING, "pthread_create: %s", strerror(err));
        return -err;
    }
    thr_channel[tid_nextpos].chnid = ptr->id;
    ++tid_nextpos;
    return 0;
}

int thr_channel_destroy(struct mlib_listentry_st *ptr){
    int i;

    for(i = 0; i< CHNNR; i++){
        if(thr_channel[i].chnid == ptr->id){
            if(pthread_cancel(thr_channel[i].tid) != 0){
                syslog(LOG_ERR, "thread of Channel %d", ptr->id);
                return -ESRCH;
            }
            pthread_join(thr_channel[i].tid, NULL);
            thr_channel[i].chnid = -1;
            return 0;
        }
    }
    syslog(LOG_ERR, "Channel %d dosen't exist", ptr->id);
    return -ESRCH;
}




int thr_channel_destroyall(void){
    int i;
    for(i = 0; i< CHNNR; i++){
        if(thr_channel[i].chnid > 0){
            if(pthread_cancel(thr_channel[i].tid) != 0){
                syslog(LOG_ERR, "thread of Channel %d", thr_channel[i].chnid);
                return -ESRCH;
            }
            pthread_join(thr_channel[i].tid, NULL);
            thr_channel[i].chnid = -1;
            return 0;
        }
    }
}



