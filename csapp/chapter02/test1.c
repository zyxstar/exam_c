#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;


int bin(int num, char *data){
    if (num == 0) return 0;
    int idx = bin(num / 2, data);
    data[idx] = num % 2 + '0';
    return idx + 1;
}

void format_bin(int num){
    char data[129] = {0};
    bin(num, data);
    int len = strlen(data);
    int fix_len = (len % 8) ? (8 - len % 8) : 0;
    if(fix_len)
        printf("%0*d", fix_len, 0);
    int i, j;
    for(i = 0, j = fix_len + 1; data[i] != 0; i++, j++){
        printf("%c", data[i]);
        if(j % 8 == 0) printf(" ");
    }

    //printf("%3d : %8s", num, data);
}


void show_bytes(byte_pointer start, int len){
    int i;
    for(i = 0; i < len; i++)
        printf(" %.2x", start[i]);

    printf("\t");
    for(i = 0; i < len; i++){
        format_bin(start[i]);
    }

    printf("\n");
}



void show_int(int x){
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_1(){
    int val = 0x87654321;
    byte_pointer valp = (byte_pointer)&val;
    show_bytes(valp, 1);
    show_bytes(valp, 2);
    show_bytes(valp, 3);

    show_int(12345);
    show_float(12345.0);

    show_bytes("12345", 6);

    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s) + 1);
}


void inplace_swap(int *x, int *y){
    if(x == y) return;
    *y = *x ^ *y; // a        a^b
    *x = *x ^ *y; // a^(a^b)  a^b
    *y = *x ^ *y; // a^(a^b)  (a^(a^b))^(a^b)
}

void test_2(){
    int a = 1;
    int b = 0;
    inplace_swap(&a, &b);
    printf("%d %d\n", a, b);
}

void set_1(unsigned int x){//保留最低有效字节,其它为0
    unsigned int y = 0xFF&x;
    show_bytes(&y, sizeof(y));
}

void set_2(unsigned int x){//保留最低有效字节,其它取补
    unsigned int y = ~x;
    show_bytes(&y, sizeof(y));
}

void test_3(){
    unsigned int x = 0x87654321;
    set_1(x);
    set_2(x);

}

int main(){
    // test_1();
    // test_2();
    test_3();



    return 0;
}

