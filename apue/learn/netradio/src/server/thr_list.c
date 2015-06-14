#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <time.h>


#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <proto.h>
#include <thr_list.h>
#include <medialib.h>
#include <server_conf.h>

static pthread_t tid_list;

static struct mlib_listentry_st *list_ent;
static int nr_list_ent;

static void *thr_list(void *unused){
    int i, totalsize, size, ret;
    struct msg_list_st *entlistp;
    struct msg_listentry_st *entryp;
    struct timespec t;

    totalsize = sizeof(chnid_t);
    for(i = 0; i < nr_list_ent; i++){
        totalsize += sizeof(struct msg_listentry_st) + strlen(list_ent[i].desc) -1 + 1;//-descr[1], +'\0'
    }

    entlistp = malloc(totalsize);
    if(entlistp == NULL){
        syslog(LOG_ERR, "malloc(): %s", strerror(errno));
        exit(1);
    }

    entlistp->id = LISTCHNID;
    entryp = entlistp->entry;

    for(i = 0; i < nr_list_ent; i++){
        size = sizeof(struct msg_listentry_st) + strlen(list_ent[i].desc);
        entryp->id = list_ent[i].id;
        entryp->len = htons(size);
        strcpy(entryp->descr, list_ent[i].desc);
        entryp = (void *)(((char *)entryp) + size);
    }

    while(1){
        ret = sendto(serversd, entlistp, totalsize, 0, (void *)&sndaddr, sizeof(sndaddr));
        if(ret < 0){
            syslog(LOG_WARNING, "sendto() :%s %s", __FUNCTION__, strerror(errno));
        }else{
            syslog(LOG_DEBUG, "sendto() :%s suceeded.", __FUNCTION__);
        }

        t.tv_sec = 1;
        t.tv_nsec = 0;
        while(nanosleep(&t, &t) != 0){
            if(errno != EINTR){
                syslog(LOG_WARNING, "nanosleep() %s", strerror(errno));
            }
        }

    }
}

int thr_list_create(struct mlib_listentry_st *listp, int nr_ent){
    int err;

    list_ent = listp;
    nr_list_ent = nr_ent;
    err = pthread_create(&tid_list, NULL, thr_list, NULL);
    if(err){
        syslog(LOG_ERR, "pthread_create(): %s", strerror(err));
        return -err;
    }
    return 0;
}

int thr_list_destroy(void){
    pthread_cancel(tid_list);
    pthread_join(tid_list, NULL);

    return 0;
}

