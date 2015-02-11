int simple(int *xp, int y){
    int t = *xp + y;
    *xp = t;
    return t;
}


// simple:
//     pushl   %ebp              save frame pointer
//     movl    %esp, %ebp        create new frame pointer
//     movl    8(%ebp), %edx     retrieve xp
//     movl    12(%ebp), %eax    retrieve y
//     addl    (%edx), %eax      add *xp to get t
//     movl    %eax, (%edx)      store t at xp
//     popl    %ebp              restore frame pointer
//     ret


// ()为指向地址
