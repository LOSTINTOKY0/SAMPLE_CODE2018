	.file	"thermo_update.c"
	.text
	.globl	set_temp_from_ports
	.type	set_temp_from_ports, @function
set_temp_from_ports:
.LFB53:
	.cfi_startproc
	movzwl	THERMO_SENSOR_PORT(%rip), %eax
	cmpw	$-1536, %ax
	ja	.L7
	shrw	$6, %ax
	subw	$500, %ax
	movw	%ax, (%rdi)
	testb	$1, THERMO_STATUS_PORT(%rip)
	je	.L3
	movzwl	THERMO_SENSOR_PORT(%rip), %edx
	movl	%edx, %ecx
	andl	$63, %ecx
	cmpw	$31, %cx
	jbe	.L4
	cmpw	$31999, %dx
	ja	.L5
	subl	$1, %eax
	movw	%ax, (%rdi)
.L4:
	movswl	(%rdi), %eax
	leal	(%rax,%rax,8), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	%edx
	sarl	$31, %ecx
	subl	%ecx, %edx
	addw	$320, %dx
	movw	%dx, (%rdi)
	movb	$1, 2(%rdi)
	movl	$0, %eax
	ret
.L5:
	addl	$1, %eax
	movw	%ax, (%rdi)
	jmp	.L4
.L3:
	movzwl	THERMO_SENSOR_PORT(%rip), %edx
	andl	$63, %edx
	cmpw	$31, %dx
	jbe	.L6
	addl	$1, %eax
	movw	%ax, (%rdi)
.L6:
	movzbl	2(%rdi), %eax
	cmpb	$1, %al
	jbe	.L11
	movl	$1, %eax
	ret
.L11:
	cmpw	$500, (%rdi)
	jle	.L9
	testb	%al, %al
	je	.L10
	movl	$0, %eax
	ret
.L7:
	movl	$1, %eax
	ret
.L9:
	movl	$0, %eax
	ret
.L10:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE53:
	.size	set_temp_from_ports, .-set_temp_from_ports
	.globl	set_display_from_temp
	.type	set_display_from_temp, @function
set_display_from_temp:
.LFB54:
	.cfi_startproc
	cmpw	$-1536, THERMO_SENSOR_PORT(%rip)
	ja	.L35
	movl	%edi, %r8d
	sall	$8, %r8d
	sarl	$24, %r8d
	cmpb	$1, %r8b
	jle	.L43
	movl	$1, %eax
	ret
.L43:
	cmpw	$-500, %di
	jge	.L14
	testb	%r8b, %r8b
	je	.L37
.L14:
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	testw	%di, %di
	js	.L44
	movl	$0, %r9d
.L15:
	movswl	%di, %eax
	imull	$-31981, %eax, %edx
	shrl	$16, %edx
	addl	%edi, %edx
	sarw	$9, %dx
	movl	%edi, %ebp
	sarw	$15, %bp
	subl	%ebp, %edx
	movswl	%dx, %ecx
	imull	$26215, %ecx, %ecx
	sarl	$18, %ecx
	movl	%edx, %r11d
	sarw	$15, %r11w
	subl	%r11d, %ecx
	leal	(%rcx,%rcx,4), %ecx
	leal	(%rcx,%rcx), %r11d
	movl	%edx, %ecx
	subl	%r11d, %ecx
	movswl	%cx, %r11d
	movl	%r11d, %edx
	sarl	$31, %edx
	xorl	%edx, %r11d
	subl	%edx, %r11d
	imull	$5243, %eax, %edx
	sarl	$19, %edx
	subl	%ebp, %edx
	movswl	%dx, %ebx
	imull	$26215, %ebx, %ebx
	sarl	$18, %ebx
	movl	%edx, %r12d
	sarw	$15, %r12w
	subl	%r12d, %ebx
	leal	(%rbx,%rbx,4), %ebx
	leal	(%rbx,%rbx), %r12d
	subl	%r12d, %edx
	movswl	%dx, %edx
	movl	%edx, %ebx
	sarl	$31, %ebx
	xorl	%ebx, %edx
	subl	%ebx, %edx
	imull	$26215, %eax, %eax
	sarl	$18, %eax
	subl	%ebp, %eax
	movswl	%ax, %ebx
	imull	$26215, %ebx, %ebx
	sarl	$18, %ebx
	movl	%eax, %ebp
	sarw	$15, %bp
	subl	%ebp, %ebx
	leal	(%rbx,%rbx,4), %ebx
	leal	(%rbx,%rbx), %ebp
	movl	%eax, %ebx
	subl	%ebp, %ebx
	movswl	%bx, %ebx
	movl	%ebx, %ebp
	sarl	$31, %ebp
	xorl	%ebp, %ebx
	subl	%ebp, %ebx
	leal	(%rax,%rax,4), %eax
	leal	(%rax,%rax), %ebp
	subl	%ebp, %edi
	movswl	%di, %edi
	movl	%edi, %eax
	sarl	$31, %eax
	xorl	%eax, %edi
	subl	%eax, %edi
	movl	$0, %eax
	movl	$0, %r13d
	movl	$0, %r12d
	jmp	.L16
.L44:
	movl	$64, %r9d
	jmp	.L15
.L46:
	sall	$7, %r9d
	movl	%eax, %r13d
	movl	%edx, %r10d
	movl	$0, %r12d
	jmp	.L18
.L47:
	sall	$7, %r9d
	movl	%ebx, %r10d
	movl	$0, %r13d
	jmp	.L18
.L48:
	sall	$7, %r9d
	movl	%edi, %r10d
	jmp	.L18
.L49:
	movl	%r11d, %r10d
	movl	$1, %r12d
	jmp	.L18
.L23:
	orl	$63, %r9d
.L22:
	addl	$1, %eax
.L16:
	cmpl	$3, %eax
	jg	.L45
	cmpl	$1, %eax
	je	.L46
	cmpl	$2, %eax
	je	.L47
	cmpl	$3, %eax
	je	.L48
	testl	%eax, %eax
	je	.L49
.L18:
	testl	%r10d, %r10d
	jne	.L21
	testw	%cx, %cx
	sete	%bpl
	testb	%r12b, %bpl
	jne	.L22
	movl	%r11d, %ebp
	orl	%edx, %ebp
	jne	.L23
	cmpl	$1, %r13d
	jne	.L23
	sarl	$7, %r9d
	jmp	.L22
.L21:
	cmpl	$1, %r10d
	je	.L50
	cmpl	$2, %r10d
	je	.L51
	cmpl	$3, %r10d
	je	.L52
	cmpl	$4, %r10d
	je	.L53
	cmpl	$5, %r10d
	je	.L54
	cmpl	$6, %r10d
	je	.L55
	cmpl	$7, %r10d
	je	.L56
	cmpl	$8, %r10d
	je	.L57
	cmpl	$9, %r10d
	jne	.L22
	orl	$111, %r9d
	jmp	.L22
.L50:
	orl	$6, %r9d
	jmp	.L22
.L51:
	orl	$91, %r9d
	jmp	.L22
.L52:
	orl	$79, %r9d
	jmp	.L22
.L53:
	orl	$102, %r9d
	jmp	.L22
.L54:
	orl	$109, %r9d
	jmp	.L22
.L55:
	orl	$125, %r9d
	jmp	.L22
.L56:
	orl	$7, %r9d
	jmp	.L22
.L57:
	orl	$127, %r9d
	jmp	.L22
.L45:
	cmpb	$1, %r8b
	je	.L58
	orl	$268435456, %r9d
.L34:
	movl	%r9d, (%rsi)
	movl	$0, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L58:
	.cfi_restore_state
	orl	$536870912, %r9d
	jmp	.L34
.L35:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	movl	$1, %eax
	ret
.L37:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE54:
	.size	set_display_from_temp, .-set_display_from_temp
	.globl	thermo_update
	.type	thermo_update, @function
thermo_update:
.LFB52:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movl	$0, 4(%rsp)
	movl	$0, (%rsp)
	leaq	4(%rsp), %rdi
	call	set_temp_from_ports
	testl	%eax, %eax
	je	.L65
	movl	$1, %eax
.L59:
	movq	8(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L66
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L65:
	.cfi_restore_state
	movq	%rsp, %rsi
	movl	4(%rsp), %edi
	call	set_display_from_temp
	testl	%eax, %eax
	jne	.L63
	movl	(%rsp), %edx
	movl	%edx, THERMO_DISPLAY_PORT(%rip)
	jmp	.L59
.L63:
	movl	$1, %eax
	jmp	.L59
.L66:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE52:
	.size	thermo_update, .-thermo_update
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
