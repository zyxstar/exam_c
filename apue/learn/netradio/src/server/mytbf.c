#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <syslog.h>
#include <string.h>


#include <mytbf.h>

struct mytbf_st{
    int cps; //bytes per second 既mp3播放速率
    int burst; //突发量 既桶的容量
    int token; //现有token数量
    pthread_mutex_t mut;
    pthread_cond_t cond;
};

static struct mytbf_st *tbf[TBFMAX];
static pthread_mutex_t mut_tbf = PTHREAD_MUTEX_INITIALIZER;

static pthread_t tid_timer;

static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static void *thr_timer(void *unused){
    int i;
    struct timespec t;
    while(1){
        t.tv_sec = 1;
        t.tv_nsec = 0;
        while(nanosleep(&t, &t) != 0){
            if(errno != EINTR){
                syslog(LOG_ERR, "nanosleep() %s", strerror(errno));
                exit(1);
            }
        }
        for (i = 0; i < TBFMAX; ++i){
            if(tbf[i] != NULL){
                pthread_mutex_lock(&tbf[i]->mut);
                tbf[i]->token += tbf[i]->cps;
                if(tbf[i]->token > tbf[i]->burst){
                    tbf[i]->token = tbf[i]->burst;
                }
                pthread_cond_broadcast(&tbf[i]->cond);
                pthread_mutex_unlock(&tbf[i]->mut);

            }
        }
    }
}

static void module_unload(void){
    pthread_cancel(tid_timer);
    pthread_join(tid_timer, NULL);
}

static void module_load(void){
    int err;
    err = pthread_create(&tid_timer, NULL, thr_timer, NULL);
    if(err){
        syslog(LOG_ERR, "pthread_create() %s", strerror(errno));
        exit(1);
    }
    atexit(module_unload);
}

static int get_free_pos(void){
    int i;
    for (i = 0; i < TBFMAX; ++i){
        if(tbf[i] == NULL){
            return i;
        }
    }
    return -1;
}

static int min(int a, int b){
    return a <= b ? a : b;
}

mytbf_t *mytbf_init(int cps, int burst){
    struct mytbf_st *me;
    int pos;

    pthread_once(&init_once, module_load);

    me = malloc(sizeof(*me));
    if(me == NULL){
        return NULL;
    }

    pthread_mutex_lock(&mut_tbf);
    pos = get_free_pos();

    if(pos < 0){
        pthread_mutex_unlock(&mut_tbf);
        free(me);
        return NULL;
    }
    tbf[pos] = me;
    pthread_mutex_unlock(&mut_tbf);

    me->cps = cps;
    me->burst = burst;
    me->token = 0;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);

    return me;
}

int mytbf_destroy(mytbf_t *ptr){
    struct mytbf_st *me = ptr;
    pthread_cond_destroy(&me->cond);
    pthread_mutex_destroy(&me->mut);

    free(me);
    return 0;
}

int mytbf_fetchtoken(mytbf_t *ptr, int n){
    struct mytbf_st *me = ptr;
    int token;

    pthread_mutex_lock(&me->mut);
    while(me->token <= 0){
        pthread_cond_wait(&me->cond, &me->mut);
    }
    token = min(me->token, n);
    me->token -= token;
    pthread_mutex_unlock(&me->mut);

    return token;
}

int mytbf_returntoken(mytbf_t *ptr, int n){
    if(n <= 0) return 0;
    struct mytbf_st *me = ptr;

    pthread_mutex_lock(&me->mut);
    me->token += n;
    if(me->token > me->burst){
        me->token = me->burst;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);

    return 0;
}
