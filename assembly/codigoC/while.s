	.file	"while.c"
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	1
	.globl	d
	.bss
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
	.globl	z
	.data
	.align 32
	.type	z, @object
	.size	z, 36
z:
	.long	1
	.long	2
	.long	3
	.long	4
	.long	5
	.long	6
	.long	7
	.long	9
	.zero	4
	.globl	t
	.align 4
	.type	t, @object
	.size	t, 4
t:
	.long	1078774989
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.long	1045220557
	.globl	f
	.type	f, @object
	.size	f, 1
f:
	.byte	112
	.text
	.globl	operator
	.type	operator, @function
operator:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$6, a(%rip)
	movl	$2, b(%rip)
	movl	a(%rip), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	%eax, d(%rip)
	movl	b(%rip), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, e(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	operator, .-operator
	.globl	conditional1
	.type	conditional1, @function
conditional1:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	cmpl	%eax, %edx
	jge	.L3
	movl	-4(%rbp), %eax
	cltq
	movl	z(,%rax,4), %eax
	movl	%eax, a(%rip)
	movl	z+16(%rip), %eax
	movl	%eax, b(%rip)
	movl	$0, %eax
	jmp	.L4
.L3:
	movl	$1, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	conditional1, .-conditional1
	.globl	conditional2
	.type	conditional2, @function
conditional2:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	d(%rip), %edx
	movl	e(%rip), %eax
	cmpl	%eax, %edx
	jl	.L6
	movl	$0, %eax
	jmp	.L7
.L6:
	movl	$1, %eax
.L7:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	conditional2, .-conditional2
	.section	.rodata
.LC0:
	.string	"hello"
	.text
	.globl	printest
	.type	printest, @function
printest:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	printest, .-printest
	.globl	while_test
	.type	while_test, @function
while_test:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	jmp	.L10
.L11:
	movl	a(%rip), %eax
	addl	$1, %eax
	movl	%eax, a(%rip)
.L10:
	movl	a(%rip), %eax
	testl	%eax, %eax
	jg	.L11
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	while_test, .-while_test
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
