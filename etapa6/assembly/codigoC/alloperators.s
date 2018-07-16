	.file	"alloperators.c"
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
	.globl	e
	.align 4
	.type	e, @object
	.size	e, 4
e:
	.zero	4
	.globl	f
	.align 4
	.type	f, @object
	.size	f, 4
f:
	.zero	4
	.globl	g
	.align 4
	.type	g, @object
	.size	g, 4
g:
	.zero	4
	.globl	h
	.align 4
	.type	h, @object
	.size	h, 4
h:
	.zero	4
	.section	.rodata
.LC0:
	.string	"%d"
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
	movl	$2, a(%rip)
	movl	$1, b(%rip)
	movl	$3, c(%rip)
	movl	$2, d(%rip)
	movl	$4, e(%rip)
	movl	$4, f(%rip)
	movl	$8, g(%rip)
	movl	$2, h(%rip)
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, a(%rip)
	movl	c(%rip), %edx
	movl	d(%rip), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, c(%rip)
	movl	e(%rip), %edx
	movl	f(%rip), %eax
	imull	%edx, %eax
	movl	%eax, e(%rip)
	movl	g(%rip), %eax
	movl	h(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, g(%rip)
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	c(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	e(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	g(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
