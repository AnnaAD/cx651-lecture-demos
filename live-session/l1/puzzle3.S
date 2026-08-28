	.file	"puzzle3.c"
	.intel_syntax noprefix
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	xor	eax, eax
	xor	r8d, r8d
.L2:
	add	r8, rax
	add	rax, rdi
	cmp	rax, 41
	jle	.L2
	mov	rax, r8
	ret
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
