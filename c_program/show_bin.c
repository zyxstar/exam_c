#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


void show_bin(const char *filepath){
    FILE *fp;
    int n;
    unsigned long count = 0;
    unsigned char buf[16];

    if((fp = fopen(filepath, "rb")) == NULL)
        exit(1);
    while((n = fread(buf, 1, 16, fp)) > 0){
        int i;
        printf("%08lX  ", count);
        for(i = 0; i < n; i++)
            printf("%02X ", (unsigned)buf[i]);

        if(n < 16)
            for(i = n; i < 16; i++) printf("   ");

        printf(" ");
        for(i = 0; i < n; i++)
            putchar(isprint(buf[i]) ? buf[i] : '.');

        putchar('\n');
        count += 16;
    }
    fclose(fp);

}


int main(int argc, char **argv){

    show_bin(argv[1]);

    return 0;
}

// gcc show_bin.c -o show_bin.out
