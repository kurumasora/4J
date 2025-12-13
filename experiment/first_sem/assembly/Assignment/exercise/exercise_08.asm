	.data
	.text
	
	.globl	main
main:
	li $t0, 0 #カウンタ
	li $t1, 5 #終了値

loop:	

	beq  $t0, $t1, proc
	addi $t3, $t3, 1
	addi $t0, $t0, 1
	j loop

	.globl proc
proc:	jr $ra	
	
