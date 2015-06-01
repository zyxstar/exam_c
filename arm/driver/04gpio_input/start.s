@[lzy@Uboot]# dnw 50000000
@[root@PC]# dnw arm.bin:start.s main.c hxxx.c
@[lzy@Uboot]# go 50000000
@	mov lr, pc
@	ldr pc, =0x50000000
@	xxxxxxx
@	xxxxxx
@[lzy@Uboot]# 
.global _start
_start:

	b reset
reset:
	stmfd sp!, {r0-r12, lr}
	bl main
	ldmfd sp!, {r0-r12, pc}
	@mov pc, lr
	@bx lr



