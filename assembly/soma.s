	.globl	main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	movl	-8(%rbp), %eax
	addl	%eax, -12(%rbp)	
	movl	%eax, -4(%rbp)
	.cfi_endproc

