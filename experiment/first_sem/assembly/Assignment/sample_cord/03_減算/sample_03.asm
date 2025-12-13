	.globl	main
main:	
	addi $t0, $zero, 100
	addi $t1, $zero, -200
	sub  $t3, $t1, $t0
	jr $ra

