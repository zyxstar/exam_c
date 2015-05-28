#include <stdio.h>

int main(void)
{
	int a = 4;

	//a++;
	//memory---->rx
	//add
	//rx---->memory

	asm volatile(
		"ldr r0, %0\n"//r0=*addr
		"add r0, r0, #1\n"
		"str r0, %0\n"//*addr=r0
		:
		:"m"(a)
		:"r0", "memory"
	);

	printf("a = %d\n", a);

	int b[3] = {0, 1, 2};
	
	asm volatile(
		//1/"add %0, %0, #1\n"
		//1/"add %1, %1, #1\n"
		//1/"add %2, %2, #1\n"
		//1/:"+r"(b[0]), "+r"(b[1]), "+r"(b[2])
		//1/:
		//1/:
		//2/"mov r0, %0\n"
		//2/"ldr r1, [r0]\n"//r1=*r0
		//2/"add r1, r1, #4\n"
		//2/"str r1, [r0]\n"//*r0=r1

		//2/"add r0, r0, #4\n"
		//2/"ldr r1, [r0]\n"
		//2/"add r1, r1, #4\n"
		//2/"str r1, [r0]\n"

		//2/"add r0, r0, #4\n"
		//2/"ldr r1, [r0]\n"
		//2/"add r1, r1, #4\n"
		//2/"str r1, [r0]\n"

		//3/"mov r0, %0\n"

		//3/"ldr r1, [r0]\n"//r1=*r0
		//3/"add r1, r1, #3\n"
		//3/"str r1, [r0], #4\n"//*r0=r1 r0+=4

		//3/"ldr r1, [r0]\n"//r1=*r0
		//3/"add r1, r1, #3\n"
		//3/"str r1, [r0], #4\n"//*r0=r1 r0+=4

		//3/"ldr r1, [r0]\n"//r1=*r0
		//3/"add r1, r1, #3\n"
		//3/"str r1, [r0], #4\n"//*r0=r1 r0+=4

		//4/"mov r0, %0\n"
		//4/"ldr r1, [r0]\n"
		//4/"add r1, r1, #2\n"
		//4/"str r1, [r0]\n"
		//4/
		//4/"ldr r1, [r0, #4]\n"//r1=*(r0+4)
		//4/"add r1, r1, #2\n"
		//4/"str r1, [r0, #4]\n"
		//4/
		//4/"ldr r1, [r0, #8]\n"//r1=*(r0+4)
		//4/"add r1, r1, #2\n"
		//4/"str r1, [r0, #8]\n"

		"mov r0, %0\n"
		"ldr r1, [r0]\n"
		"add r1, r1, #5\n"
		"str r1, [r0]\n"

		"ldr r1, [r0, #4]!\n"//r0+=4 r1=*r0
		"add r1, r1, #5\n"
		"str r1, [r0]\n"
		
		"ldr r1, [r0, #4]!\n"//r0+=4 r1=*r0
		"add r1, r1, #5\n"
		"str r1, [r0]\n"
		:
		:"r"(b)
		:"r0", "r1"
	);

	int i;
	for(i = 0; i < 3; i++)
		printf("b[%d] = %d\n", i, b[i]);

	

	return 0;
}
#if 0
atomic_t a;

atomic_add(a, 1);

int atomic_add(int a, int b)
{
	asm volatile(
		"again:\n"
		"ldrex r0, %0\n"
		"add r0, r0, %1\n"
		"strex r1, r0, %0\n"
		"cmp r1, #0\n"
		"bne again\n"
		:
		:"m"(a), "r"(b)
		:
	);
}
#endif



