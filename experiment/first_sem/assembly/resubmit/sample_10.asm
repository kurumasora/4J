	.data
	.text

	.globl	main
main:	
	addi $t0, $zero, 1
	addi $t1, $zero, 2
	slt  $t2, $t0, $t1
	jr $ra
