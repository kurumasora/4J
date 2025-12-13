	.data
	.text
	
	.globl	main
main:
	add $t0, $zero, $zero	
	addi  $t1, $zero, 5

loop:	beq  $t0, $t1, proc
	addi $t1, $t1, -1
	j loop

	.globl proc
proc:	jr $ra	
	
