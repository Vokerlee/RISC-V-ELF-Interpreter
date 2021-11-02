	.file	"array_sum.c"
	.option nopic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-192
	sw	s0,188(sp)
	addi	s0,sp,192
	sw	zero,-20(s0)
	j	.L2
.L3:
	lw	a5,-20(s0)
	slli	a5,a5,2
	addi	a5,a5,-16
	add	a5,a5,s0
	lw	a4,-20(s0)
	sw	a4,-172(a5)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,39
	ble	a4,a5,.L3
	sw	zero,-24(s0)
	sw	zero,-28(s0)
	j	.L4
.L5:
	lw	a5,-28(s0)
	slli	a5,a5,2
	addi	a5,a5,-16
	add	a5,a5,s0
	lw	a5,-172(a5)
	lw	a4,-24(s0)
	add	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-28(s0)
	addi	a5,a5,1
	sw	a5,-28(s0)
.L4:
	lw	a4,-28(s0)
	li	a5,39
	ble	a4,a5,.L5
	li	a5,0
	mv	a0,a5
	lw	s0,188(sp)
	addi	sp,sp,192
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 11.1.0"
