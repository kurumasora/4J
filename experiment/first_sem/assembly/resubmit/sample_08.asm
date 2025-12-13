	.data
	.text

	.globl	main
main:	
	addi $t0, $zero, 7
	addi $t1, $zero, 1
	and  $t2, $t0, $t1
	jr $ra
