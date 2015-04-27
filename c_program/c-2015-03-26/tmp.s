	.file	"tmp.c"
	.text
.globl bar
	.type	bar, @function
bar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	bar, .-bar
.globl foo
	.type	foo, @function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$32167, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	bar
	movl	%eax, -4(%ebp)
	movl	$12345, %eax
	leave
	ret
	.size	foo, .-foo
	.ident	"GCC: (GNU) 4.4.5 20110214 (Red Hat 4.4.5-6)"
	.section	.note.GNU-stack,"",@progbits
