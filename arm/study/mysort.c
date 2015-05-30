#include <stdio.h>

void sort(int *, int);
int main(){
    int i;
    int arr[] = {3,5,7,4,2,1,9,6};
    int len = sizeof(arr) / sizeof(int);
    sort(arr, len);
    for(i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}


asm (
    "sort:\n"
    "    str fp, [sp, #-4]!\n"
    "    add fp, sp, #0\n"
    "    sub sp, sp, #28\n"
    "    str r0, [fp, #-24]\n"
    "    str r1, [fp, #-28]\n"
    "    mov r3, #0\n"
    "    str r3, [fp, #-12]\n"
    "    b   .MYLABEL1\n"
    ".MYLABLE6:\n"
    "    ldr r3, [fp, #-12]\n"
    "    str r3, [fp, #-8]\n"
    "    ldr r3, [fp, #-12]\n"
    "    add r3, r3, #1\n"
    "    str r3, [fp, #-16]\n"
    "    b   .MYLABEL2\n"
    ".MYLABEL4:\n"
    "    ldr r3, [fp, #-16]\n"
    "    mov r3, r3, asl #2\n"
    "    ldr r2, [fp, #-24]\n"
    "    add r3, r2, r3\n"
    "    ldr r2, [r3, #0]\n"
    "    ldr r3, [fp, #-8]\n"
    "    mov r3, r3, asl #2\n"
    "    ldr r1, [fp, #-24]\n"
    "    add r3, r1, r3\n"
    "    ldr r3, [r3, #0]\n"
    "    cmp r2, r3\n"
    "    bge .MYLABEL3\n"
    "    ldr r3, [fp, #-16]\n"
    "    str r3, [fp, #-8]\n"
    ".MYLABEL3:\n"
    "    ldr r3, [fp, #-16]\n"
    "    add r3, r3, #1\n"
    "    str r3, [fp, #-16]\n"
    ".MYLABEL2:\n"
    "    ldr r2, [fp, #-16]\n"
    "    ldr r3, [fp, #-28]\n"
    "    cmp r2, r3\n"
    "    blt .MYLABEL4\n"
    "    ldr r2, [fp, #-12]\n"
    "    ldr r3, [fp, #-8]\n"
    "    cmp r2, r3\n"
    "    beq .MYLABEL5\n"
    "    ldr r3, [fp, #-12]\n"
    "    mov r3, r3, asl #2\n"
    "    ldr r2, [fp, #-24]\n"
    "    add r3, r2, r3\n"
    "    ldr r3, [r3, #0]\n"
    "    str r3, [fp, #-20]\n"
    "    ldr r3, [fp, #-12]\n"
    "    mov r3, r3, asl #2\n"
    "    ldr r2, [fp, #-24]\n"
    "    add r3, r2, r3\n"
    "    ldr r2, [fp, #-8]\n"
    "    mov r2, r2, asl #2\n"
    "    ldr r1, [fp, #-24]\n"
    "    add r2, r1, r2\n"
    "    ldr r2, [r2, #0]\n"
    "    str r2, [r3, #0]\n"
    "    ldr r3, [fp, #-8]\n"
    "    mov r3, r3, asl #2\n"
    "    ldr r2, [fp, #-24]\n"
    "    add r3, r2, r3\n"
    "    ldr r2, [fp, #-20]\n"
    "    str r2, [r3, #0]\n"
    ".MYLABEL5:\n"
    "    ldr r3, [fp, #-12]\n"
    "    add r3, r3, #1\n"
    "    str r3, [fp, #-12]\n"
    ".MYLABEL1:\n"
    "    ldr r3, [fp, #-28]\n"
    "    sub r2, r3, #1\n"
    "    ldr r3, [fp, #-12]\n"
    "    cmp r2, r3\n"
    "    bgt .MYLABLE6\n"
    "    add sp, fp, #0\n"
    "    ldmfd   sp!, {fp}\n"
    "    bx  lr\n"
);


// void sort(int *arr, int len){
//     int idx, i, j, temp;
//     for(i = 0; i < len - 1; i++){
//         idx = i;
//         for(j = i + 1; j < len; j++){
//             if(arr[j] < arr[idx])
//                 idx = j;
//         }
//         if(i != idx){
//             temp = arr[i];
//             arr[i] = arr[idx];
//             arr[idx] = temp;
//         }
//     }
// }
