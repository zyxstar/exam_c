#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <setjmp.h>
#include <assert.h>
#include "list.h"

#define STAT_SIZE 256
#define INO_SIZE 32
#define UNM_SIZE 32
#define GNM_SIZE 32
#define TIME_SIZE 32
#define FILENM_SIZE 256


enum SHOW_OPTIONS{
    SHOW_ALL = 1,
    SHOW_LONG = 1 << 1,
    SHOW_INODE = 1 << 2
};

struct ls_entry{
    char ino[INO_SIZE];
    char typ;
    char perms[10];
    char user[UNM_SIZE];
    char group[GNM_SIZE];
    off_t size;
    char mtime[TIME_SIZE];
    char filenm[FILENM_SIZE];
    char lnfilenm[FILENM_SIZE];
    int bgcolor;
    int fgcolor;
    struct list_head node;
};

#define HAS_OPTION(setting, option) (((setting) & (option)) == (option))

static void parse_argv(char **argv, char **path, int *options);
static void trave_dir(char *path, int options);
static void process_file(const char *name, struct list_head *list);

static jmp_buf  jmp_trave;
static jmp_buf  jmp_process;

int main(int argc, char **argv){
    int options = 0;
    char *path = ".";

    parse_argv(argv, &path, &options);
    trave_dir(path, options);
}

static void parse_argv(char **argv, char **path, int *options){
    char *c, ch;
    while(*(++argv) != NULL){
        if(**argv == '-'){
            c = *argv;
            while((ch = *(++c)) != '\0'){
                switch(ch){
                    case 'a' : *options = *options|SHOW_ALL; break;
                    case 'l' : *options = *options|SHOW_LONG; break;
                    case 'i' : *options = *options|SHOW_INODE; break;
                    default: break;
                }
            }
        }
        else
            *path = *argv;
    }
}

static struct list_head *init_list(){
    struct list_head *list = malloc(sizeof(*list));
    assert(list != NULL);
    INIT_LIST_HEAD(list);
    return list;
}

static void destroy_list(struct list_head *list){
    struct list_head *cur;
    struct ls_entry *ls_ent;
    __list_for_each(cur, list) {
        ls_ent = list_entry(cur, struct ls_entry, node);
        free(ls_ent);
    }
    free(list);
}

static void print_ls_entry(const struct ls_entry *entry){
    printf("%s %c%s %s %s %ld %s %s %s\n", 
        entry->ino, entry->typ, entry->perms, entry->user, entry->group,
        entry->size, entry->mtime, entry->filenm, entry->lnfilenm);
}


static void trave_dir(char *path, int options){
    DIR *dir;
    struct dirent *entry;

    int ret_cd = 0;
    struct stat st;

    struct list_head *list = init_list();
    struct list_head *cur;
    struct ls_entry *ls_ent;

    if (stat(path, &st)== -1) {
        perror("stat()");
        ret_cd = 1;
        goto END;
    }

    if(!HAS_OPTION(st.st_mode, S_IFDIR)){
        process_file(path, list);
        goto SHOW;
    }

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir()");
        ret_cd = 1;
        goto END;
    }

    if (setjmp(jmp_trave) != 0){
        ret_cd = 1;
        goto CLOSE_DIR;
    }

    if(chdir(path) == -1){
        perror("chdir()");
        ret_cd = 1;
        goto CLOSE_DIR;
    }

    while (1) {
        entry = readdir(dir);
        if (entry == NULL) break;
        process_file(entry->d_name, list);
    }

SHOW:

    __list_for_each(cur, list) {
        ls_ent = list_entry(cur, struct ls_entry, node);
        print_ls_entry(ls_ent);
    }


CLOSE_DIR:
    closedir(dir);

END:
    destroy_list(list);
    exit(ret_cd);
}


static int get_idx_of_arr(int *arr, int size, int val){
    int i;
    for(i = 0; i < size; i++)
        if(arr[i] == val) return i;
    return -1;
}


static char get_file_type(mode_t mode){
    int flags[] = {S_IFSOCK, S_IFLNK, S_IFREG, S_IFBLK, S_IFDIR, S_IFCHR, S_IFIFO};
    char *types = "sl-bdcp";
    int idx = get_idx_of_arr(flags, sizeof(flags) / sizeof(int), mode);
    return idx == -1 ? ' ' :  types[idx];
}

static void get_file_perm(mode_t mode, char *perm_str){
	if(HAS_OPTION(mode, S_IRUSR))
		perm_str[0]='r';
	if(HAS_OPTION(mode, S_IWUSR))
		perm_str[1]='w';
	if(HAS_OPTION(mode, S_IXUSR))
		perm_str[2]='x';
    if(HAS_OPTION(mode, S_ISUID))
        perm_str[2]='S';
	if(HAS_OPTION(mode, S_IXUSR|S_ISUID))
		perm_str[2]='s';


	if(HAS_OPTION(mode, S_IRGRP))
		perm_str[3]='r';
	if(HAS_OPTION(mode, S_IWGRP))
		perm_str[4]='w';
	if(HAS_OPTION(mode, S_IXGRP))
		perm_str[5]='x';
    if(HAS_OPTION(mode, S_ISGID))
        perm_str[5]='S';
    if(HAS_OPTION(mode, S_IXGRP|S_ISGID))
        perm_str[5]='s';


	if(HAS_OPTION(mode, S_ISGID))
		perm_str[5]='s';
	if(HAS_OPTION(mode, S_IROTH))
		perm_str[6]='r';
	if(HAS_OPTION(mode, S_IWOTH))
		perm_str[7]='w';
	if(HAS_OPTION(mode, S_IXOTH))
		perm_str[8]='x';
	if(HAS_OPTION(mode, S_ISVTX))
		perm_str[8]='S';
    if(HAS_OPTION(mode, S_IXOTH|S_ISVTX))
        perm_str[8]='s';
}


static void get_file_username(uid_t uid, char *unm_str){
    struct passwd *pwd = getpwuid(uid);
    if(pwd == NULL){
        perror("getpwuid()");
        longjmp(jmp_process, 1);
    }
    strncpy(unm_str, pwd->pw_name, UNM_SIZE);
}

static void get_file_groupname(gid_t gid, char *gnm_str){
    struct group *grp = getgrgid(gid);
    if(grp == NULL){
        perror("getgrgid()");
        longjmp(jmp_process, 2);
    }
    strncpy(gnm_str, grp->gr_name, GNM_SIZE);
}

static void get_file_time(time_t mtime, char *time_str){
    time_t now = time(NULL);
    struct tm *ntm = localtime(&now);
    int y = ntm->tm_year;

    struct tm *ltm = localtime(&mtime);
    if(ltm->tm_year < y)
        strftime(time_str, TIME_SIZE, "%b %d  %Y", ltm);
    else
        strftime(time_str, TIME_SIZE, "%b %d %R", ltm);
}

static void get_link_filenm(const char *name, char *lnfilenm){
    ssize_t size = readlink(name, lnfilenm, FILENM_SIZE);
    if(size == -1){
        perror("readlink()");
        longjmp(jmp_process, 3);
    }
    printf("%d\n", size);
    if(size == FILENM_SIZE) lnfilenm[FILENM_SIZE - 1] = '\0';
    else lnfilenm[size] = '\0';
}

static void process_file(const char *name, struct list_head *list){
    // int is_show_long = HAS_OPTION(options, SHOW_LONG);
    // int is_show_all = HAS_OPTION(options, SHOW_ALL);
    // int is_show_inode = HAS_OPTION(options, SHOW_INODE);

    struct ls_entry *entry = malloc(sizeof(*entry));
    assert(entry != NULL);
    struct stat st;

    if (setjmp(jmp_process) != 0){
        goto ERROR;
    }

    if (lstat(name, &st) == -1) {
        perror("stat()");
        goto ERROR;        
    }

    snprintf(entry->ino, INO_SIZE, "%ld", st.st_ino);
    entry->typ = get_file_type(st.st_mode & S_IFMT);

    strncpy(entry->perms, "---------", 10);
    get_file_perm(st.st_mode, entry->perms);

    get_file_username(st.st_uid, entry->user);
    get_file_groupname(st.st_gid, entry->group);

    entry->size = st.st_size;

    get_file_time(st.st_mtime, entry->mtime);
    strncpy(entry->filenm, name, FILENM_SIZE);

    if(entry->typ == 'l'){
        get_link_filenm(name, entry->lnfilenm);
    }

    

    list_add(&entry->node, list);
    return;

ERROR:
    free(entry);
    longjmp(jmp_trave, 1);


//     if(!is_show_all && name[0] == '.')
//         return;

//     // if(is_show_inode)
//     //     printf("%-ld ", ino);

//     if(!is_show_long){
//         goto SHOW_NAME;
//     }


// SHOW_NAME:
//     //if(is_show_long && st->)
//         printf("%s\n", name);
}


// gcc myls.c -o myls
