	.data

	.globl v
v:	.word	1234
	.word   1000
	.word   2000
	.word   3000
	
	.text

	.globl	main
main:	
	addi $t0, $zero, 1
	la $t3, v
	lw $t1, 0($t3)
	sw $t1, 12($t3)
	lw $t1, 8($t3)
	sw $t1, 4($t3)
	add $t2, $t1, $t0
	jr $ra
