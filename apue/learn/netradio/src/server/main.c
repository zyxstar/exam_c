#include <stdio.h>

#include <proto.h>
#include <stdio.h>

#include <medialib.h>

static struct mlib_listentry_st *list;
static int list_size;

static void daemon_exit(int s){
    mlib_freechnlist(list);
    exit(0);
}

/*
 * -
 * -
 * -
 * -
 */

int main(){
    int err;

    err = mlib_getchnlist(&list, &list_size);
    if(err){
        fprintf(stderr, "mlib_getchnlist() : %s\n", strerror(err));
        exit(1);
    }

    thr_list_create(list, list_size);
    for(i = 0; i < list_size; ++i){
        thr_channel_create(list+i);
    }

    while(1) pause();

    exit(0);
}
