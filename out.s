.data
.comm _labelLCoMp89750,4,4
.comm _labelLCoMp89751,4,4
.comm _tMpComP9861,4,4
.comm _tMpComP9860,4,4

lit_string0:
	.string "\n"


string_integer:
	.string "%d"
.globl	e
	.align 4
	.type	e, @object
	.size	e, 4
e:
	.long	0

.globl	count
	.align 4
	.type	count, @object
	.size	count, 4
count:
	.long	0

.text
.globl	main
.type	main, @function
main:

.cfi_startproc
	pushq %rbp
	movq	%rsp, %rbp
	
._labelLCoMp89750:

### CMD LE ###
	movl count(%rip), %edx
	movl	$10, %eax
	cmpl %eax, %edx
	jg	 ._labelLCoMp89751

### CMD ADD ###
	movl count(%rip), %edx
	movl	$1, %eax
	addl %edx, %eax
	movl %eax, _tMpComP9861(%rip)

### CMD ASS ###
	movl	_tMpComP9861(%rip), %eax
	movl %eax, count(%rip)

### CMD ASS ###
	movl	count(%rip), %eax
	movl %eax, e(%rip)

### CMD PRINT ARG ###
	movl	e(%rip), %esi
	movl	$string_integer, %edi
	movl	$0, %eax
	call	printf
## cmd PRINT
	movl	$lit_string0, %edi
	movl $0, %eax
	call	printf
	jmp ._labelLCoMp89750
	
._labelLCoMp89751:
	popq	%rbp
	ret
	.cfi_endproc
