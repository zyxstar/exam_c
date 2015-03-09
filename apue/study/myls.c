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




#define STAT_SIZE 256
#define UID_SIZE 20
#define GID_SIZE 20
#define TIME_SIZE 20


enum SHOW_OPTIONS{
    SHOW_ALL = 1,
    SHOW_LONG = 1 << 1,
    SHOW_INODE = 1 << 2
};

#define HAS_OPTION(setting, option) (((setting) & (option)) == (option))

static void parse_argv(char **argv, char **path, int *options);
static void trave_dir(char *path, int options);
static void show_file(ino_t ino, const char *name, int options);

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

static void trave_dir(char *path, int options){
    DIR *dir;
    struct dirent *entry;

    int ret_cd = 0;
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir()");
        ret_cd = 1;
        goto END;
    }

    if(chdir(path) == -1){
        perror("chdir()");
        ret_cd = 1;
        goto CLOSE_DIR;
    }

    while (1) {
        entry = readdir(dir);
        if (entry == NULL) break;
        show_file(entry->d_ino, entry->d_name, options);
    }

CLOSE_DIR:
    closedir(dir);
END:
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


static void get_file_username(uid_t uid, char *uid_str){
    struct passwd *pwd = getpwuid(uid);
    if(pwd == NULL){
        perror("getpwuid()");
        exit(1);
    }
    strncpy(uid_str, pwd->pw_name, UID_SIZE);
}

static void get_file_groupname(gid_t gid, char *gid_str){
    struct group *grp = getgrgid(gid);
    if(grp == NULL){
        perror("getgrgid()");
        exit(1);
    }
    strncpy(gid_str, grp->gr_name, GID_SIZE);
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


static void get_stat(struct stat st, char *stat_str){
    char t = get_file_type(st.st_mode & S_IFMT);

    char perm_str[9] = "---------";
    get_file_perm(st.st_mode, perm_str);

    char uid_str[UID_SIZE];
    get_file_username(st.st_uid, uid_str);

    char gid_str[GID_SIZE];
    get_file_groupname(st.st_gid, gid_str);

    char time_str[TIME_SIZE];
    get_file_time(st.st_mtime, time_str);

    snprintf(stat_str, STAT_SIZE, "%c%s %s %s %10ld %s ",
            t, perm_str, uid_str, gid_str, st.st_size, time_str);
}



static void show_file(ino_t ino, const char *name, int options){
    int is_show_long = HAS_OPTION(options, SHOW_LONG);
    int is_show_all = HAS_OPTION(options, SHOW_ALL);
    int is_show_inode = HAS_OPTION(options, SHOW_INODE);


    if(!is_show_all && name[0] == '.')
        return;

    if(is_show_inode)
        printf("%-8ld", ino);

    if(!is_show_long){
        goto SHOW_NAME;
    }

    struct stat st;
    int ret;

    ret = stat(name, &st);
    if (ret == -1) {
        perror(name);
        exit(1);
    }

    char stat_str[STAT_SIZE];
    get_stat(st, stat_str);
    printf("%s ", stat_str);

SHOW_NAME:
    //if(is_show_long && st->)
        printf("%s\n", name);
}


// gcc myls.c -o myls
