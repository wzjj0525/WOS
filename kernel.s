	.file	"kernel.c"
	.text
	.globl	b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	6
	.globl	a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	5
	.text
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.size	f, .-f
	.section	.rodata
.LC0:
	.string	"Welcome to WOS!\n"
	.text
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$4, %esp
	call	screen_clean
	subl	$12, %esp
	pushl	$.LC0
	call	print
	addl	$16, %esp
	movl	a, %eax
	addl	$1, %eax
	movl	%eax, a
	nop
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
