	.file	"03in_out.c"
	.section	.rodata
.LC0:
	.string	"out = %d\n"
.LC1:
	.string	"out1 = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %r12d
	.cfi_offset 3, -32
	.cfi_offset 12, -24
	movl	%eax, %ebx
#APP
# 10 "03in_out.c" 1
	mov %r12d, #3
mov %ebx, #4

# 0 "" 2
#NO_APP
	movl	%r12d, -24(%rbp)
	movl	%ebx, -20(%rbp)
	movl	$.LC0, %eax
	movl	-24(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %eax
	movl	-20(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
