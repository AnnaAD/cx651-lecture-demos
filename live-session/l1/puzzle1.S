	.file	"puzzle1.c"
	.intel_syntax noprefix
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	mov	eax, 2147483649
	add	rax, rdi
	imul	rax, rax, 12314452
	ret
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
