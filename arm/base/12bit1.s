	.cpu arm1176jzf-s
	.eabi_attribute 27, 3
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"12bit1.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"lsl = %d\012\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, fp, lr}
	add	fp, sp, #20
	sub	sp, sp, #16
#APP
@ 6 "12bit1.c" 1
	mov r0, #30
mov r7, r0, lsl #2

@ 0 "" 2
	str	r7, [fp, #-24]
	str	r6, [fp, #-28]
	str	r5, [fp, #-32]
	str	r4, [fp, #-36]
	ldr	r3, .L2
	mov	r0, r3
	ldr	r1, [fp, #-24]
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp!, {r4, r5, r6, r7, fp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
