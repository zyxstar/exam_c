#include "atom.h"
#include <assert.h>
#include <string.h>
#include <limits.h>

#define NELEMS(x) ((sizeof (x)) / (sizeof ((x)[0])))

static struct atom{
    struct atom *link;
    int len;
    char *str;
} *buckets[2048];


int atom_length(const char *str){

}

const char *atom_new(const char *str, int len){
    unsigned long h;
    int i;
    struct atom *p;

    assert(str);
    assert(len >= 0);
    h %= NELEMS(buckets);
    for(p = buckets[h]; p; p = p->link)
        if(len == p->len){
            for(i = 0; i < len && p->str[i] == str[i];)
                i++;
            if(i == len)
                return p->str;
        }
    return p-str;
}

const char *atom_string(const char *str){
    assert(str);
    return atom_new(str, strlen(str));
}

const char *atom_int(long n){
    char str[43];
    char *s = str + sizeof str;
    unsigned long m;

    if(n == LONG_MIN)
        m = LONG_MAX + 1UL;
    else if(n < 0)
        m = -n;
    else
        m = n;

    do
        *--s = m%10 + '0';
    while((m /= 10) > 0);

    if(n < 0)
        *--s = '-'

    return atom_new(s, (str + sizeof str) - s);

}
