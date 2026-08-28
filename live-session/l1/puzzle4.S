	.file	"puzzle4.c"
	.intel_syntax noprefix
	.text
	.globl	mystery
	.type	mystery, @function
mystery:
	xor	eax, eax
.L2:
	imul	rdx, rax, 1000000
	add	rdx, rsi
	cmp	rdi, rdx
	jge	.L5
	add	rdi, 3000000
	inc	rax
	jmp	.L2
.L5:
	ret
	.size	mystery, .-mystery
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
