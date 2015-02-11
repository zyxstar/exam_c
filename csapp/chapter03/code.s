	.file	"code.c"
	.intel_syntax
	.text
.globl sum
	.type	sum, @function
sum:
	push	%ebp
	mov	%ebp, %esp
	mov	%eax, DWORD PTR [%ebp+12]
	add	%eax, DWORD PTR [%ebp+8]
	add	DWORD PTR accum, %eax
	pop	%ebp
	ret
	.size	sum, .-sum
.globl accum
	.bss
	.align 4
	.type	accum, @object
	.size	accum, 4
accum:
	.zero	4
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-54)"
	.section	.note.GNU-stack,"",@progbits
