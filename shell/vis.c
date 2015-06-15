#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int strip = 0;

void vis(FILE *fp){
    int c;
    while((c = getc(fp)) != EOF){
        if(isascii(c) &&
            (isprint(c) || c=='\n' || c=='\t' || c==' '))
            putchar(c);
        else if(!strip)
            printf("\\%03o", c);
    }
}


int main(int argc, char **argv){
    int i;
    FILE *fp;

    while(argc > 1 && argv[1][0] == '-'){
        switch(argv[1][1]){
            case 's':
                strip = 1;
                break;
            default:
                fprintf(stderr, "%s: unknonw arg %s\n", argv[0], argv[1]);
                exit(1);
        }
        argc--;
        argv++;
    }

    if(argc == 1){
        vis(stdin);
    }
    else
        for(i = 1; i < argc; i++){
            if((fp = fopen(argv[i], "r")) == NULL){
                fprintf(stderr, "%s: can't open %s\n", argv[0], argv[i]);
                exit(1);
            } else{
                vis(fp);
                fclose(fp);
            }
        }

    return 0;
}

