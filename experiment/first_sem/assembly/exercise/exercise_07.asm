.text
.globl main
main:
    li $t0, 2 
    li $t1, 4
    slt $t2, $t0, $t1
    beq $t2, $zero, skip
    addi $t1, $t1, 1000




skip:
    li $v0, 10
    syscall