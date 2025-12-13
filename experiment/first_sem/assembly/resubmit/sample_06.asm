	.data

	.globl v
v:	.word	1234
	.word	5678
	
	.text

	.globl	main
main:	
	la $t3, v
	lw $t0, 0($t3)
	lw $t1, 4($t3)	
	jr $ra

	
