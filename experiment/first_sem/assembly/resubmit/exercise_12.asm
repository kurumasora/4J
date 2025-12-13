    .data

    .globl v

v:  .word 3, 2, 1, 4, 5, 8, 17, 12, 10, 5


Size: .word 10

.text

.globl sum

sum:	la 	$t0, v
	addi 	$t1, $zero, 0
	lw 	$t2, 0($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 4($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 8($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 12($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 16($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 20($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 24($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 28($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 32($t0)
	add 	$t1, $t1, $t2
	lw 	$t2, 36($t0)
    add 	$t1, $t1, $t2
	move	$t9, $t1

.globl main

main:   la $t0, v
        move $t3, $ra
        jal sum
        move $ra, $t3
        jr $ra

    
	

	



