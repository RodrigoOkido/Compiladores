	.globl	main
	.type	main, @function
main:

	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_endproc
