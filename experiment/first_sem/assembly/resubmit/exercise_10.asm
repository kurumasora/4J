.globl main
main:
    add $t0, $zero, $zero      
    add $t8, $zero, $zero      
    addi $t3, $zero, 2         
    addi $t4, $zero, 2         

loop_1:
    beq $t0, $t3, proc         
    add $t1, $zero, $zero      

    loop_2:
        beq $t1, $t4, next  
        addi $t8, $t8, 1           
        addi $t1, $t1, 1           
        j loop_2                 

next:
    addi $t0, $t0, 1                             
    jr loop_1

.globl proc
proc:
    jr $ra                      