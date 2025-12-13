	.data

	.globl v
v:	.word	0
	.word	0
	.text

	.globl	main
main:	
	la $t3, v
	addi $t0, $zero, 1234
	addi $t1, $zero, 5678	
	sw $t0, 0($t3)
	sw $t1, 4($t3)	
	jr $ra
