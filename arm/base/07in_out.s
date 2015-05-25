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
	.file	"07in_out.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	add	fp, sp, #28
	sub	sp, sp, #32
	mov	r3, #1
	str	r3, [fp, #-32]
	mov	r3, #2
	str	r3, [fp, #-36]
	mov	r3, #3
	str	r3, [fp, #-40]
	mov	r3, #5
	str	r3, [fp, #-44]
	ldr	ip, [fp, #-32]
	ldr	r4, [fp, #-36]
	ldr	r5, [fp, #-40]
	ldr	r6, [fp, #-44]
#APP
@ 19 "07in_out.c" 1
mov r0, ip
mov r1, r4
mov r2, r5
mov r3, r6

mov r9, r0
mov sl, r1
mov r8, r2
mov r7, r3

@ 0 "" 2
	str	r9, [fp, #-48]
	str	sl, [fp, #-52]
	str	r8, [fp, #-56]
	str	r7, [fp, #-60]
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #28
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	bx	lr
	.size	main, .-main
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
