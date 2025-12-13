	.data
	.text

	.globl	fact
fact:	addi 	$sp, $sp, -8
	sw   	$ra, 0($sp)
	sw 	$a0, 4($sp)
	slti	$t0, $a0, 1
	beq	$t0, $zero, L1
	addi	$v0, $zero, 1
	addi	$sp, $sp, 8
	jr 	$ra

	.globl	L1
L1:	addi	$a0, $a0, -1
	jal	fact
	lw	$ra, 0($sp)
	lw	$a0, 4($sp)
	addi	$sp, $sp, 8
	mul	$v0, $a0, $v0
	jr	$ra
	
	.globl main
main:	addi 	$t0, $t0, 4
	addi 	$sp, $sp, -8
	sw 	$ra  0($sp)
	sw	$t0, 4($sp)
	move	$a0, $t0
	jal 	fact
	move 	$t1, $v0
	lw	$ra, 0($sp)
	lw	$t0, 4($sp)
	addi	$sp, $sp, 8
	jr 	$ra


	
