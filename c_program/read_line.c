#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define INIT_ALLOC_LEN (4)

typedef struct{
    char *buffer;
    int used_len;
    int alloc_len;
} LineStatus;

static void line_status_new(LineStatus *l){
    l->used_len = 0;
    l->alloc_len = INIT_ALLOC_LEN;
    l->buffer = malloc(INIT_ALLOC_LEN * sizeof(char));
    assert(l->buffer != NULL);
}

static void add_character(LineStatus *l, char ch){
    assert(l->alloc_len >= l->used_len);

    if(l->used_len == l->alloc_len){
        l->alloc_len *= 2;
        l->buffer = realloc(l->buffer, l->alloc_len * sizeof(char));
        assert(l->buffer != NULL);
    }

    l->buffer[l->used_len] = ch;
    l->used_len++;
}

static void line_status_free(LineStatus *l){
    free(l->buffer);
}

char *read_line(FILE *fp){
    char ch, *ret_line;
    LineStatus line_status;
    line_status_new(&line_status);

    while((ch = getc(fp)) != EOF){
        if(ch == '\n'){
            add_character(&line_status, '\0');
            break;
        }
        add_character(&line_status, ch);
    }
    if(ch == EOF){
        if(line_status.used_len > 0){
            add_character(&line_status, '\0');
        }else{
            return NULL;
        }
    }
    ret_line = malloc(line_status.used_len * sizeof(char));
    strcpy(ret_line, line_status.buffer);
    line_status_free(&line_status);
    return ret_line;
}

char **add_line(char **text_data, char *line,
                int *line_alloc_num, int *line_num){
    assert(*line_alloc_num >= *line_num);
    if(*line_alloc_num == *line_num){
        text_data = realloc(text_data, (*line_alloc_num + INIT_ALLOC_LEN) * sizeof(char*));
        *line_alloc_num += INIT_ALLOC_LEN;
    }
    text_data[*line_num] = line;
    (*line_num)++;
    return text_data;
}

char **read_file(FILE *fp, int *ret_line_num_p){
    char **text_data = NULL;
    int line_num = 0;
    int line_alloc_num = 0;
    char *line;

    while((line = read_line(fp)) != NULL){
        text_data = add_line(text_data, line, &line_alloc_num, &line_num);
    }
    *ret_line_num_p = line_num;
    return text_data;
}

int main(int argc, const char *argv[]){
    char **text_data;
    int line_num;
    int i = 0;
    FILE *fp = fopen("input.txt", "r");

    text_data = read_file(fp, &line_num);

    for(; i < line_num; i++){
        printf("%s\n", text_data[i]);
        free(text_data[i]);
    }
    free(text_data);
    return 0;
}
