	.file	"ifandcomparators.c"
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.zero	4
	.globl	d
	.align 4
	.type	d, @object
	.size	d, 4
d:
	.zero	4
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"igual"
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
	movl	$8, a(%rip)
	movl	$5, b(%rip)
	movl	$7, c(%rip)
	movl	$7, d(%rip)
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	cmpl	%eax, %edx
	jle	.L2
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L3
.L2:
	movl	b(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L3:
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	cmpl	%eax, %edx
	jge	.L4
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L4:
	movl	b(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L5:
	movl	c(%rip), %edx
	movl	d(%rip), %eax
	cmpl	%eax, %edx
	jl	.L6
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L7
.L6:
	movl	c(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L7:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
