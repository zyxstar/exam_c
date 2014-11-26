#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#define DEBUG

#ifdef DEBUG
#define DEBUG_WRITE(arg) debug_write arg
#else
#define DEBUG_WRITE(arg)
#endif

#define INIT_ALLOC_LEN (4)

void debug_write(char *format, ...){
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}


typedef struct{
    void *buffer;
    int elem_size;
    int used_len;
    int alloc_len;
    void(*free_fn)(void*);
} Cache;

static void cache_new(Cache *c, int elem_size, void(*free_fn)(void*)) {
    assert(elem_size > 0);
    c->elem_size = elem_size;
    c->used_len = 0;
    c->alloc_len = INIT_ALLOC_LEN;
    c->buffer = malloc(INIT_ALLOC_LEN * elem_size);
    c->free_fn = free_fn;
    assert(c->buffer != NULL);
}

static void cache_grow(Cache *c){
    DEBUG_WRITE(("-cache_grow_b: %d\n", c->alloc_len));
    c->alloc_len *= 2;
    c->buffer = realloc(c->buffer, c->alloc_len * sizeof(c->elem_size));
    assert(c->buffer != NULL);
}

static void cache_add(Cache *c, void *data_addr){
    assert(c->alloc_len >= c->used_len);
    if(c->used_len == c->alloc_len){
        cache_grow(c);
    }
    void *target = (char*)c->buffer + c->used_len * c->elem_size;
    memcpy(target, data_addr, c->elem_size);

    #ifdef DEBUG //debug write
        if(c->elem_size == sizeof(char)){
            DEBUG_WRITE(("-cache_add_char_s: %c\n", *(char*)data_addr));
            DEBUG_WRITE(("-cache_add_char_t: %c\n", ((char*)c->buffer)[c->used_len]));
        }
        else if (c->elem_size == sizeof(char*)){
            DEBUG_WRITE(("-cache_add_char*_s: %s\n", *(char**)data_addr));
            DEBUG_WRITE(("-cache_add_char*_t: %s\n", ((char**)c->buffer)[c->used_len]));
        }
    #endif

    c->used_len++;
}

static void cache_free(Cache *c){
    int i;
    if(c->free_fn != NULL){
        for(i = 0; i < c->used_len; i++){
            c->free_fn(c->buffer + i * c->elem_size);
        }
    }
    #ifdef DEBUG
        if(c->elem_size == sizeof(char)){
            DEBUG_WRITE(("-cache_free_char*: %s\n", (char*)c->buffer));
        }
        else if (c->elem_size == sizeof(char*)){
            DEBUG_WRITE(("-cache_free_char**\n"));
        }
    #endif
    free(c->buffer);
}

char *read_line(FILE *fp){
    char ch, temp_ch, *ret_line;
    Cache cache;
    cache_new(&cache, sizeof(char), NULL);

    while((ch = getc(fp)) != EOF){
        if(ch == '\n'){
            temp_ch = '\0';
            cache_add(&cache, &temp_ch);
            break;
        }
        cache_add(&cache, &ch);
    }
    if(ch == EOF){
        if(cache.used_len > 0){
            temp_ch = '\0';
            cache_add(&cache, &temp_ch);
        }else{
            return NULL;
        }
    }
    ret_line = malloc(cache.used_len * sizeof(char));
    strcpy(ret_line, (char*)cache.buffer);
    cache_free(&cache);
    return ret_line;
}

void string_free(void* elemAddr) {
    char** p = (char**)elemAddr;
    DEBUG_WRITE(("-string_free: %s\n", *p));
    free(*p);
}

char **read_file(FILE *fp, int *ret_line_num){
    char *temp_line, **ret_file_data;
    Cache cache;

    // cache_new(&cache, sizeof(char*), string_free);
    cache_new(&cache, sizeof(char*), NULL);
    while((temp_line = read_line(fp)) != NULL){
        // must use &, so add `char**`
        cache_add(&cache, &temp_line);
    }
    // not *ret_file_data = ...
    ret_file_data = malloc(cache.used_len * sizeof(char*));

    memcpy(ret_file_data, cache.buffer, cache.used_len * sizeof(char*));
    *ret_line_num = cache.used_len;
    cache_free(&cache);

    return ret_file_data;
}

int main(int argc, const char *argv[]){
    char **file_data;
    int i, line_num;
    FILE *fp = fopen("input.txt", "r");

    file_data = read_file(fp, &line_num);

    for(i = 0; i < line_num; i++){
        printf("%s\n", file_data[i]);
        free(file_data[i]);
    }
    free(file_data);
    return 0;
}
