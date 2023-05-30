	.file	"sort-c-rot13.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
.LC0:
	.string	"nopqrstuvwxyzabcdefghijklm"
	.text
	.align	2
	.globl	strCmp
	.type	strCmp, @function
strCmp:
	addi	sp,sp,-32
	lui	a5,%hi(.LC0)
	addi	a5,a5,%lo(.LC0)
	lw	t1,0(a5)
	lw	a7,4(a5)
	lw	a6,8(a5)
	lw	a2,12(a5)
	lw	a3,16(a5)
	lw	a4,20(a5)
	sw	t1,4(sp)
	sw	a7,8(sp)
	sw	a6,12(sp)
	sw	a2,16(sp)
	sw	a3,20(sp)
	sw	a4,24(sp)
	lhu	a5,24(a5)
	sh	a5,28(sp)
	li	a2,25
	j	.L5
.L3:
	bne	a5,a4,.L4
	addi	a0,a0,1
	addi	a1,a1,1
	beq	a5,zero,.L4
.L5:
	lbu	a5,0(a0)
	lbu	a4,0(a1)
	addi	a3,a5,-97
	andi	a3,a3,0xff
	bgtu	a3,a2,.L2
	addi	a5,a5,32
	add	a5,a5,sp
	lbu	a5,-125(a5)
.L2:
	addi	a3,a4,-97
	andi	a3,a3,0xff
	bgtu	a3,a2,.L3
	addi	a4,a4,32
	add	a4,a4,sp
	lbu	a4,-125(a4)
	j	.L3
.L4:
	sub	a0,a5,a4
	addi	sp,sp,32
	jr	ra
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
	bgeu	a0,s3,.L8
	mv	s4,a0
	mv	s0,a0
	j	.L12
.L10:
	sw	s2,0(s0)
	sw	s1,4(s0)
	mv	s0,s4
.L12:
	lw	s1,0(s0)
	lw	s2,4(s0)
	mv	a1,s2
	mv	a0,s1
	call	strCmp
	bgt	a0,zero,.L10
	addi	s0,s0,4
	bgtu	s3,s0,.L12
.L8:
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
