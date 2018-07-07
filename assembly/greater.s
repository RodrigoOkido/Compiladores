	.globl	main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	popq	%rbp
	.cfi_endproc

