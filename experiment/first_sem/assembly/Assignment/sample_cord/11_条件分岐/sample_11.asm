	.data
	.text

	.globl addplus
addplus:
	addi $t2, $t0, 1
	jr $ra	
	
	.globl	main
main:
	add  $t2, $zero, $zero
	addi $t0, $zero, 0
	addi $t1, $zero, 1	
	beq  $t0, $t1, addplus
	jr $ra
