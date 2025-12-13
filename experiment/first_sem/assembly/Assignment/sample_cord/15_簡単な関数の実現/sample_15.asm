	.data
	.text

	.globl	sum
sum:	addi 	$sp, $sp, -4
	sw   	$t0, 0($sp)
	addi 	$t0, $zero, 0
	add  	$t0, $a0, $t0
	add  	$t0, $a1, $t0
	add  	$t0, $a2, $t0
	move 	$v0, $t0	
	lw 	$t0, 0($sp)
	addi 	$sp, $sp, 4
	jr 	$ra
	
	.globl main
main:	addi 	$t0, $t0, 1
	addi 	$t1, $t1, 2
	addi 	$t2, $t2, 3
	addi 	$t3, $zero, 10
	move 	$a0, $t0
	move 	$a1, $t1
	move 	$a2, $t2
	move 	$t5, $ra
	jal 	sum
	move 	$t4, $v0
	add	$t4, $t3, $t4
	move 	$ra, $t5
	jr 	$ra
