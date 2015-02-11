	.file	"simple.c"
	.text
.globl simple
	.type	simple, @function
simple:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	(%edx), %eax
	movl	%eax, (%edx)
	popl	%ebp
	ret
	.size	simple, .-simple
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)"
	.section	.note.GNU-stack,"",@progbits
