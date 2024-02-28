.align 2

.data
array: .word 7 -8 -9 0 100 932047 12 12 -400

.text
.globl main

main:
    la $t0, array # load the address
    li $t1, 0 # sum = 0
    li $t2, 9 # upper_bound = 9
    li $t3, 0 # counter = 0

loop:
    lw $t4, 0($t0) # load value of address $t0
    add $t1, $t1, $t4 # add the value of $t4 to the sum $t1
    addi $t0, $t0, 4 # go to next word in the array
    addi $t3, $t3, 1 # counter++
    bne $t3, $t2, loop # loop if counter != 12

    li $v0, 1
    move $a0, $t1
    syscall # print out sum

exit:
    li $v0, 10
    syscall

