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
    if( num == 0){
        printf("%08d ", 0);
        return;
    }

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
    unsigned int y = 0xFF & x;
    show_bytes((byte_pointer)&y, sizeof(y));
}

void set_2(unsigned int x){//保留最低有效字节,其它取补
    unsigned int y = ~0xFF ^ x; //与1异或可以取补
    show_bytes((byte_pointer)&y, sizeof(y));
}

void set_3(unsigned int x){//最低字节全成1,其它字节不变
    unsigned int y = 0xFF | x;
    show_bytes((byte_pointer)&y, sizeof(y));
}


void test_3(){
    unsigned int x = 0x87654321;
    set_1(x);
    set_2(x);
    set_3(x);

}


unsigned is_equal(unsigned x, unsigned y){
    return !(x ^ y);
}

unsigned bool_xor(unsigned x, unsigned y){
    return (x & ~y) | (~x & y);
}

void test_4(){//位移k 大于w位 时,只位移 k mod w 位  ??
    int d = 0xFEDCBA98;
    int lval = 0xFEDCBA98 << 32; //位移0
    int aval = 0xFEDCBA98 >> 36; //位移4
    unsigned uval = 0xFEDCBA98u << 40; //位移8

    show_bytes((byte_pointer)&d, sizeof(d));
    show_bytes((byte_pointer)&lval, sizeof(lval));
    show_bytes((byte_pointer)&aval, sizeof(aval));
    show_bytes((byte_pointer)&uval, sizeof(uval));

}

void test_5(){
    short x = 12345;
    short mx = -x;

    show_bytes((byte_pointer)&x, sizeof(short));
    show_bytes((byte_pointer)&mx, sizeof(short));

}

void hex_2_den(int x){
    printf("%d\n", x);
}

void test_6(){
    hex_2_den(0x1b8);
    hex_2_den(0x14);
    hex_2_den(0xfffffe58);

}

void test_7(){
    short v = -12345;
    unsigned short uv = (unsigned short) v;
    printf("v = %d, uv = %u\n", v, uv);

    int x = -1;
    unsigned u = 2147483648;

    printf("x %u %d\n", x, x);
    printf("u %u %d\n", u, u);

}

int strlonger(char *s, char *t){
    return strlen(s) - strlen(t) > 0;
}

void test_8(){
    printf("%d\n", strlonger("abcddd", "defd"));
}

int main(){
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    // test_5();
    // test_6();
    // test_7();
    test_8();


    return 0;
}

