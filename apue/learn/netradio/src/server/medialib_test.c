#include <stdio.h>
#include <stdlib.h>

#include <server_conf.h>
#include <medialib.h>

struct server_conf_st server_conf = {
    .media_dir = DEFAULT_MEDIADIR
};

int main(){
    int err, i;
    struct mlib_listentry_st *list;
    int list_size;

    err = mlib_getchnlist(&list, &list_size);
    if(err){
        perror("mlib_getchnlist()\n");
        exit(1);
    }

    for(i = 0; i < list_size; i++){
        printf("CHN: %d %s\n", list[i].id, list[i].desc);
    }

    return 0;
}
