	.arch armv7-a
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
	.file	"05.c"
	.text
	.align	2
	.global	mylongadd
	.type	mylongadd, %function
mylongadd:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	mov	r2, #12
	mov	r3, #0
	strd	r2, [fp, #-12]
	mov	r2, #34
	mov	r3, #0
	strd	r2, [fp, #-20]
	ldrd	r0, [fp, #-12]
	ldrd	r2, [fp, #-20]
	adds	r2, r2, r0
	adc	r3, r3, r1
	strd	r2, [fp, #-28]
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	mylongadd, .-mylongadd
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	bl	mylongadd
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp!, {fp, pc}
	.size	main, .-main
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
