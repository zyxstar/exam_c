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
	.file	"mysort.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d \000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #40
	movw	r3, #:lower16:C.6.2617
	movt	r3, #:upper16:C.6.2617
	sub	ip, fp, #44
	mov	lr, r3
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r3, #8
	str	r3, [fp, #-12]
	sub	r3, fp, #44
	mov	r0, r3
	ldr	r1, [fp, #-12]
	bl	sort
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L3:
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	ldr	r1, [fp, #-8]
	mvn	r2, #39
	mov	r1, r1, asl #2
	sub	r0, fp, #4
	add	r1, r0, r1
	add	r2, r1, r2
	ldr	r2, [r2, #0]
	mov	r0, r3
	mov	r1, r2
	bl	printf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	blt	.L3
	mov	r0, #10
	bl	putchar
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
	.size	main, .-main
	.align	2
	.global	sort
	.type	sort, %function
sort:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L5
.L10:
	ldr	r3, [fp, #-12]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-16]
	b	.L6
.L8:
	ldr	r3, [fp, #-16]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	ldr	r1, [fp, #-24]
	add	r3, r1, r3
	ldr	r3, [r3, #0]
	cmp	r2, r3
	bge	.L7
	ldr	r3, [fp, #-16]
	str	r3, [fp, #-8]
.L7:
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L6:
	ldr	r2, [fp, #-16]
	ldr	r3, [fp, #-28]
	cmp	r2, r3
	blt	.L8
	ldr	r2, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	beq	.L9
	ldr	r3, [fp, #-12]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r3, [r3, #0]
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-12]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [fp, #-8]
	mov	r2, r2, asl #2
	ldr	r1, [fp, #-24]
	add	r2, r1, r2
	ldr	r2, [r2, #0]
	str	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-24]
	add	r3, r2, r3
	ldr	r2, [fp, #-20]
	str	r2, [r3, #0]
.L9:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L5:
	ldr	r3, [fp, #-28]
	sub	r2, r3, #1
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	bgt	.L10
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	sort, .-sort
	.section	.rodata
	.align	2
	.type	C.6.2617, %object
	.size	C.6.2617, 32
C.6.2617:
	.word	3
	.word	5
	.word	7
	.word	4
	.word	2
	.word	1
	.word	9
	.word	6
	.ident	"GCC: (ctng-1.8.1-FA) 4.5.1"
	.section	.note.GNU-stack,"",%progbits
