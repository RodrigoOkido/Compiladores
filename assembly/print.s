.LC0:
	.string	"oi"
	.globl	main
main:
	.cfi_startproc
	pushq	%rbp
	movl	$.LC0, %edi
	call	printf
	popq	%rbp
	.cfi_endproc
