	.data

	.globl v
v:	.word 1
	.word 2
	.word 3
	.word 4

	.text
	
	.globl sum
sum:	addi $t1, $zero, 0
	lw $t2, 0($t0)
	add $t1, $t1, $t2
	lw $t2, 4($t0)
	add $t1, $t1, $t2
	lw $t2, 8($t0)
	add $t1, $t1, $t2
	lw $t2, 12($t0)
	add $t1, $t1, $t2
	jr $ra
	
	.globl main
main:	la $t0, v
	move $t3, $ra
	jal sum
	move $ra, $t3
	jr $ra
