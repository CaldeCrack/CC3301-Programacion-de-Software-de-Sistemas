	.file	"sort-c-rot13.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	strCmp
	.type	strCmp, @function
strCmp:
	li	a3,96
	li	a2,109
	li	a6,122
	j	.L7
.L3:
	bgtu	a5,a6,.L2
	addi	a5,a5,-13
	andi	a5,a5,0xff
.L2:
	bleu	a4,a3,.L4
	bgtu	a4,a2,.L5
	addi	a4,a4,13
	andi	a4,a4,0xff
.L4:
	bne	a5,a4,.L6
	addi	a0,a0,1
	addi	a1,a1,1
	beq	a5,zero,.L6
.L7:
	lbu	a5,0(a0)
	lbu	a4,0(a1)
	bleu	a5,a3,.L2
	bgtu	a5,a2,.L3
	addi	a5,a5,13
	andi	a5,a5,0xff
	j	.L2
.L5:
	bgtu	a4,a6,.L4
	addi	a4,a4,-13
	andi	a4,a4,0xff
	j	.L4
.L6:
	sub	a0,a5,a4
	ret
	.size	strCmp, .-strCmp
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	sw	s4,8(sp)
	slli	s3,a1,2
	addi	s3,s3,-4
	add	s3,a0,s3
	bgeu	a0,s3,.L9
	mv	s4,a0
	mv	s0,a0
	j	.L13
.L11:
	sw	s2,0(s0)
	sw	s1,4(s0)
	mv	s0,s4
.L13:
	lw	s1,0(s0)
	lw	s2,4(s0)
	mv	a1,s2
	mv	a0,s1
	call	strCmp
	bgt	a0,zero,.L11
	addi	s0,s0,4
	bgtu	s3,s0,.L13
.L9:
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	lw	s4,8(sp)
	addi	sp,sp,32
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
