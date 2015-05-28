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
	.file	"05in_out.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"out = %d\012\000"
	.align	2
.LC1:
	.ascii	"in_out = %d\012\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, fp, lr}
	add	fp, sp, #12
	sub	sp, sp, #16
	mov	r3, #5
	str	r3, [fp, #-16]
	mov	r3, #6
	str	r3, [fp, #-20]
	mov	r3, #100
	str	r3, [fp, #-24]
	ldr	r3, [fp, #-16]
	ldr	r2, [fp, #-24]
	mov	r4, r2
#APP
@ 9 "05in_out.c" 1
	mov r5, r4
mov r4, r3

@ 0 "" 2
	str	r5, [fp, #-20]
	str	r4, [fp, #-24]
	ldr	r3, .L2
	mov	r0, r3
	ldr	r1, [fp, #-20]
	bl	printf
	ldr	r3, .L2+4
	mov	r0, r3
	ldr	r1, [fp, #-24]
	bl	printf
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #12
	ldmfd	sp!, {r4, r5, fp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	.word	.LC1
	.size	main, .-main
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
