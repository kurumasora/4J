	.data

	.globl v
v:	.word	0

	.text

	.globl	main
main:	
	addi $t0, $zero, 1
	addi $t1, $zero, 2	
	add $t2, $t1, $t0
	la $t3, v
	sw $t2, 0($t3)
	jr $ra
