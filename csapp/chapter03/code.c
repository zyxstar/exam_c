int accum = 0;
int sum(int x, int y){
    int t = x + y;
    accum += t;
    return t;
}


// gcc -O1 -S code.c
// gcc -O1 -c code.c
// objdump -d code.o

// sum:
//     pushl   %ebp
//     movl    %esp, %ebp
//     movl    12(%ebp), %eax
//     addl    8(%ebp), %eax
//     addl    %eax, accum
//     popl    %ebp
//     ret

// sum:
//     push    %ebp
//     mov %ebp, %esp
//     mov %eax, DWORD PTR [%ebp+12]
//     add %eax, DWORD PTR [%ebp+8]
//     add DWORD PTR accum, %eax
//     pop %ebp
//     ret


// 字节8 字16 双字32 四字64
// %eax %ecx %edx 普通
// %ebp %esp 程序栈
//
