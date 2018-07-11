.data
.comm _tMpComP9864,4,4
.comm _labelLCoMp89750,4,4
.comm _tMpComP9863,4,4
.comm _labelLCoMp89751,4,4
.comm _tMpComP9862,4,4
.comm _tMpComP9861,4,4
.comm _labelLCoMp89752,4,4
.comm _tMpComP9860,4,4

lit_string0:
	.string "j"

.comm _labelLCoMp89753,4,4
.comm _tMpComP9868,4,4
.comm _tMpComP9867,4,4
.comm _labelLCoMp89754,4,4
.comm _tMpComP9866,4,4
.comm _labelLCoMp89755,4,4
.comm _tMpComP9865,4,4

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
	.long	1

.globl	d
.align 4
.type	d, @object
.size	d, 4
d:
	.long	0

.globl	e
.align 4
.type	e, @object
.size	e, 4
e:
	.long	0

.globl	z
.align 32
.type	z, @object
.size	40, 4
z:
	.long	10

.globl	t
.align 4
.type	t, @object
.size	t, 4
t:
	.long	3.2

.globl	c
.align 4
.type	c, @object
.size	c, 4
c:
	.long	0.2

.globl	f
.align 4
.type	f, @object
.size	f, 4
f:
	.long	'p'

.text
.globl	operator
.type	operator, @function
operator:

.cfi_startproc
pushq %rbp
movq	%rsp, %rbp

### CMD ADD ###
movl	$1, %edx
movl	$5, %eax
addl %edx, %eax
movl %eax, _tMpComP9860(%rip)

### CMD ASS ###
movl	_tMpComP9860(%rip), %eax
movl %eax, a(%rip)

### CMD SUB ###
movl	$5, %edx
movl	$3, %eax
subl %eax, %edx
movl %edx, _tMpComP9861(%rip)

### CMD ASS ###
movl	_tMpComP9861(%rip), %eax
movl %eax, b(%rip)

### CMD MUL ###
movl a(%rip), %edx
movl	$5, %eax
imull %edx, %eax
movl %eax, _tMpComP9862(%rip)

### CMD ASS ###
movl	_tMpComP9862(%rip), %eax
movl %eax, d(%rip)

### CMD DIV ###

movl b(%rip), %eax
movl	$2, %ecx
cltd
idivl	%ecx
movl %eax, _tMpComP9863(%rip)

### CMD ASS ###
movl	_tMpComP9863(%rip), %eax
movl %eax, e(%rip)
popq	%rbp
ret
.cfi_endproc

.text
.globl	conditional1
.type	conditional1, @function
conditional1:

.cfi_startproc
pushq %rbp
movq	%rsp, %rbp

### CMD LESS ###
movl a(%rip), %edx
movl b(%rip), %eax
cmpl %eax, %edx
jge ._labelLCoMp89750

### CMD VEC_INDEX ###
movl	z+0(%rip), %eax
movl	%eax, _tMpComP9865(%rip)

### CMD ASS ###
movl	_tMpComP9865(%rip), %eax
movl %eax, a(%rip)
jmp ._labelLCoMp89751

._labelLCoMp89750:

movl	%r8d, %edx
movl	%r9d, %ecx
movl	%edi, %r8d
movl	%eax, %r9d
## cmd PRINT
movl	$lit_string0, %edi
	call	printf

._labelLCoMp89751:
popq	%rbp
ret
.cfi_endproc

.text
.globl	conditional2
.type	conditional2, @function
conditional2:

.cfi_startproc
pushq %rbp
movq	%rsp, %rbp

### CMD GREATER ###
movl d(%rip), %edx
movl e(%rip), %eax
cmpl %eax, %edx
jle ._labelLCoMp89752

### CMD RETURN ###
movl	$0, %eax

._labelLCoMp89752:

### CMD RETURN ###
movl	$1, %eax
popq	%rbp
ret
.cfi_endproc

.text
.globl	returntest
.type	returntest, @function
returntest:

.cfi_startproc
pushq %rbp
movq	%rsp, %rbp

### CMD ASS ###
movl	5.3(%rip), %eax
movl %eax, c(%rip)

### CMD RETURN ###
movl	c(%rip), %eax
popq	%rbp
ret
.cfi_endproc

.text
.globl	while_test
.type	while_test, @function
while_test:

.cfi_startproc
pushq %rbp
movq	%rsp, %rbp

._labelLCoMp89754:

### CMD GREATER ###
movl a(%rip), %edx
movl	$0, %eax
cmpl %eax, %edx
jle ._labelLCoMp89755

### CMD ADD ###
movl a(%rip), %edx
movl	$1, %eax
addl %edx, %eax
movl %eax, _tMpComP9868(%rip)

### CMD ASS ###
movl	_tMpComP9868(%rip), %eax
movl %eax, a(%rip)
jmp ._labelLCoMp89754

._labelLCoMp89755:
popq	%rbp
ret
.cfi_endproc
