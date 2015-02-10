	.file	"env01.c"
.globl static_variable
	.data
	.align 4
	.type	static_variable, @object
	.size	static_variable, 4
static_variable:
	.long	5
	.text
.globl f
	.type	f, @function
f:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movl	$1, -28(%rbp)
	movl	$2, -32(%rbp)
	movl	$3, -36(%rbp)
	movl	$4, -40(%rbp)
	movl	$5, -44(%rbp)
	movl	$6, -48(%rbp)
	movl	$7, -52(%rbp)
	movl	$8, -56(%rbp)
	movl	$9, -60(%rbp)
	movl	$10, -64(%rbp)
	movl	$110, %ebx
	.cfi_offset 3, -24
	movl	$1, a_very_long_name_to_see_how_long_they_can_be(%rip)
	movl	-64(%rbp), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	movl	$10, %edi
	movl	$0, %eax
	call	func_ret_int
	movl	%eax, -32(%rbp)
	movl	$0, %eax
	call	func_ret_double
	movsd	%xmm0, -24(%rbp)
	movq	%rbx, %rdi
	movl	$0, %eax
	call	func_ret_char_ptr
	movq	%rax, %rbx
	addq	$56, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	f, .-f
.globl func_ret_int
	.type	func_ret_int, @function
func_ret_int:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, %eax
	movl	-24(%rbp), %edx
	subl	$6, %edx
	movl	%edx, -4(%rbp)
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %ecx
	leal	(%rcx,%rdx), %edx
	leal	(%rdx,%rax), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	func_ret_int, .-func_ret_int
.globl func_ret_double
	.type	func_ret_double, @function
func_ret_double:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movabsq	$4614253070214989087, %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	func_ret_double, .-func_ret_double
.globl func_ret_char_ptr
	.type	func_ret_char_ptr, @function
func_ret_char_ptr:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$1, %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	func_ret_char_ptr, .-func_ret_char_ptr
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-3)"
	.section	.note.GNU-stack,"",@progbits
