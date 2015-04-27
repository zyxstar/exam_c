	.file	"switch.c"
	.section	.rodata
.LC0:
	.string	"tmp"
	.text
.globl bar
	.type	bar, @function
bar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$5, 8(%ebp)
	jne	.L2
	movl	$0, 4(%esp)
	movl	$.LC0, (%esp)
	call	open
.L2:
	movl	$6, (%esp)
	call	close
	leave
	ret
	.size	bar, .-bar
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.5 20110214 (Red Hat 4.4.5-6)"
	.section	.note.GNU-stack,"",@progbits
