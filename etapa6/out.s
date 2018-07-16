.data
.comm _tMpComP9860,4,4

.LC0:
	.string "\n"


string_integer:
	.string "%d"
.globl	a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	0

.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	0

.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.long	5

.globl	d
	.align 4
	.type	d, @object
	.size	d, 4
d:
	.long	7

.text
.globl	soma
.type	soma, @function
soma:

.cfi_startproc
	pushq %rbp
	movq	%rsp, %rbp

### CMD ADD ###
	movl c(%rip), %edx
	movl d(%rip), %eax
	addl %edx, %eax
	movl %eax, _tMpComP9860(%rip)

### CMD ASS ###
	movl %eax, a(%rip)
	movl	a(%rip), %eax

### CMD RETURN ###
	movl	a(%rip), %eax
	popq	%rbp
	ret
	.cfi_endproc

.text
.globl	main
.type	main, @function
main:

.cfi_startproc
	pushq %rbp
	movq	%rsp, %rbp

### CMD CALL FUNCTION ### 
	movl	$0, %eax
	call soma

### CMD ASS ###
	movl %eax, b(%rip)
	movl	b(%rip), %eax
## cmd PRINT
	movl	b(%rip), %esi
	movl	$string_integer, %edi
	movl	$0, %eax
	call	printf
## cmd PRINT
	movl	$.LC0, %edi
	movl $0, %eax
	call	printf
	popq	%rbp
	ret
	.cfi_endproc
