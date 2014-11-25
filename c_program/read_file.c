#include "read_line.h"

char **add_line(char **text_data, char *line,
                int *line_alloc_num, int *line_num){
    assert(*line_alloc_num >= *line_num);
    if(*line_alloc_num == *line_num){
        text_data = realloc(text_data, (*line_alloc_num + ALLOC_SIZE) * sizeof(char*));
        *line_alloc_num += ALLOC_SIZE;
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
