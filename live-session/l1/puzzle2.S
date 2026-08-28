	.file	"puzzle2.c"
	.intel_syntax noprefix
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	imul	rax, rdi, 20001
	cmp	rdi, 300000
	jle	.L1
	imul	rax, rdi, 8000001
.L1:
	ret
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
