	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 1
	.globl	_function                       ## -- Begin function function
	.p2align	4, 0x90
_function:                              ## @function
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	%rdi, -40(%rbp)
	leaq	-32(%rbp), %rdi
	movq	-40(%rbp), %rsi
	movl	$16, %edx
	callq	___strcpy_chk
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB0_2
## %bb.1:
	addq	$48, %rsp
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$288, %rsp                      ## imm = 0x120
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -276(%rbp)
	movl	$0, -280(%rbp)
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$255, -280(%rbp)
	jge	LBB1_4
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movslq	-280(%rbp), %rax
	movb	$65, -272(%rbp,%rax)
## %bb.3:                               ##   in Loop: Header=BB1_1 Depth=1
	movl	-280(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -280(%rbp)
	jmp	LBB1_1
LBB1_4:
	leaq	-272(%rbp), %rdi
	callq	_function
	movl	-276(%rbp), %eax
	movl	%eax, -284(%rbp)                ## 4-byte Spill
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB1_6
## %bb.5:
	movl	-284(%rbp), %eax                ## 4-byte Reload
	addq	$288, %rsp                      ## imm = 0x120
	popq	%rbp
	retq
LBB1_6:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
