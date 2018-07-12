	.file	"or.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -12(%rbp)
	movl	$1, -8(%rbp)
	cmpl	$0, -12(%rbp)
	jne	.L2
	cmpl	$0, -8(%rbp)
	je	.L3
.L2:
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
	movl	%eax, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	test
	.type	test, @function
test:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -12(%rbp)
	movl	$1, -8(%rbp)
	cmpl	$0, -12(%rbp)
	jne	.L6
	cmpl	$0, -8(%rbp)
	je	.L7
.L6:
	movl	$1, %eax
	jmp	.L8
.L7:
	movl	$0, %eax
.L8:
	movl	%eax, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	test, .-test
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
