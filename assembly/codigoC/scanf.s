	.file	"scanf.c"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	1
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	1
	.globl	v
	.bss
	.align 4
	.type	v, @object
	.size	v, 4
v:
	.zero	4
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\n"
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
	movl	$v, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	jmp	.L2
.L3:
	movl	v(%rip), %edx
	movl	b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, v(%rip)
	movl	v(%rip), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
.L2:
	movl	a(%rip), %eax
	cmpl	$9, %eax
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
