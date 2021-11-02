	.file	"multiplier.c"
	.option nopic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	li	a5,19
	sw	a5,-20(s0)
	li	a5,8
	sw	a5,-24(s0)
	lw	a1,-24(s0)
	lw	a0,-20(s0)
	call	mult
	sw	a0,-28(s0)
	li	a5,0
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.align	2
	.globl	mult
	.type	mult, @function
mult:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	zero,-20(s0)
	j	.L4
.L6:
	lw	a5,-40(s0)
	andi	a5,a5,1
	beq	a5,zero,.L5
	lw	a4,-20(s0)
	lw	a5,-36(s0)
	add	a5,a4,a5
	sw	a5,-20(s0)
.L5:
	lw	a5,-40(s0)
	srai	a5,a5,1
	sw	a5,-40(s0)
	lw	a5,-36(s0)
	slli	a5,a5,1
	sw	a5,-36(s0)
.L4:
	lw	a5,-40(s0)
	bne	a5,zero,.L6
	lw	a5,-20(s0)
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	mult, .-mult
	.ident	"GCC: (GNU) 11.1.0"
