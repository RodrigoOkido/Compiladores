	.globl	main
main:

	.cfi_startproc
	movq	%rsp, %rbp	
	movl	-12(%rbp), %eax
	imull	-8(%rbp), %eax	
	movl	%eax, -4(%rbp)
	.cfi_endproc

