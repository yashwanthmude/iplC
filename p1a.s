	.section	.rodata
	.text
	.globl	foo
	.type	foo, @function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0, %esp
	movl	8(%ebp),%eax
	addl	$0,%eax
	movl	%eax,%edx
	movl	(%eax),%eax
	movl	$2,(%edx)
	movl	8(%ebp),%eax
	addl	$0,%eax
	movl	%eax,%edx
	movl	(%eax),%eax
	movl	%eax,%ebx
	pushl	%ebx
	pushl	$.LC0
	call	printf
	addl	$8,%esp
	movl	$0,%eax
	jmp	.L2
.L2:
	nop
	leave
	ret
.LC0: 
	.string	"%d\n"
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$44, %esp
	movl	$0,-44(%ebp)
	jmp	.L4
.L5:
	movl	$-40,%eax
	movl	-44(%ebp),%ebx
	imull	$4,%ebx
	addl	%ebx,%eax
	movl	%eax,%edx
	movl	(%ebp,%eax,1),%eax
	movl	-44(%ebp),%eax
	movl	%eax,(%ebp,%edx,1)
	movl	-44(%ebp),%eax
	addl	$1,%eax
	movl	%eax,-44(%ebp)
.L4:
	movl	$10,%eax
	cmpl	%eax,-44(%ebp)
	setl	%al
	movzbl	%al,%eax
	cmpl	$0,%eax
	jne	.L5
	pushl	-40(%ebp)
	call	foo
	addl	$4,%esp
	movl	%eax,%ebx
	pushl	%ebx
	pushl	$.LC1
	call	printf
	addl	$8,%esp
	movl	$0,%eax
	jmp	.L3
.L3:
	nop
	leave
	ret
.LC1: 
	.string	"%d\n"
