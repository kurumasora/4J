.data
	.globl 	v
v:	.word 3, 2, 1, 4, 5, 8, 17, 12, 10, 5
	
	.text

	.globl	main
main:	la $a0, v
	li $a1, 10
	jal sum

	move $t9, $v0
	
	li $v0, 10
	syscall

sum:	li $v0, 0
	li $t0, 0	

sumloop:
	bge $t0, $a1, sumend

	sll $t1, $t0, 2
	add $t2, $a0, $t1
	lw  $t3, 0($t2)
	
	add $v0, $v0, $t3
	
	addi $t0, $t0, 1
	j sumloop

sumend:
	jr $ra
