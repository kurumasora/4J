	.data

	.globl v
v:	.word	1111
	.word   2222
	.word   3333
	.word   4444
	
	.text

	.globl	main
main:	
	
	la $t3, v
	lw $t1, 0($t3)
	sw $t1, 12($t3)
	lw $t1, 8($t3)
	sw $t1, 4($t3)

	jr $ra
