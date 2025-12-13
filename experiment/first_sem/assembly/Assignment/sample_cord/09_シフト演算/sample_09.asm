	.data
	.text

	.globl	main
main:	
	addi $t0, $zero, 1
	sll  $t1, $t0, 3
	jr $ra
