	.globl	main
main:
	.cfi_startproc
	movq	%rsp, %rbp
	jmp	.L2
.L3:
	addl	$1, -4(%rbp)
.L2:
	cmpl	$2, -4(%rbp)
	jle	.L3
	.cfi_endproc

