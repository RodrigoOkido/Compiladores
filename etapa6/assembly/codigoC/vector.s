	.file	"vector.c"
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.zero	4
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.zero	4
	.globl	b
	.data
	.align 8
	.type	b, @object
	.size	b, 12
b:
	.long	7
	.long	3
	.long	5
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n\n"
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
	movl	$4, b+4(%rip)
	movl	b+4(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	b+4(%rip), %eax
	addl	$3, %eax
	movl	%eax, c(%rip)
	movl	c(%rip), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L3:
	movl	i(%rip), %eax
	cltq
	movl	b(,%rax,4), %edx
	movl	a(%rip), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L2:
	movl	i(%rip), %eax
	cmpl	$2, %eax
	jle	.L3
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
