.align 2

.data
prompt: .asciiz "This program calculates the i-th term of the series Sn=3n-2+Sn-1, enter a wanted a value for i: "
nln: .asciiz "\n"

.text
.globl main

main:

    # printing the prompt
    la $a0, prompt
    li $v0, 4
    syscall

    # read in the value of i and initialize it
    li $v0, 5
    syscall
    move $t0, $v0

    jal recursion

    # print a new line
    la $a0, nln
    li $v0, 4
    syscall

    # print the result 
    move $a0, $t1
    li $v0, 1
    syscall

    # exit
    li $v0, 10
    syscall


recursion:

    # Sn = 3 * n - 2 + Sn-1
    addi $sp, $sp, -8
    sw $ra, 0($sp)

    # using $a0 as the current argument
    # base case: if i <= 0 
    ble $t0, $zero, base_case

    # preserving current $a0 as we didn't go to base_case
    sw $t0, 4($sp)

    addi $t0, $t0, -1

    jal recursion

    # load current argument
    lw $t2, 4($sp)

    # adding the current term of the series to the sum of all previous terms
    # updating Sn-1

    # 3n
    mul $t2, $t2, 3

    # Sn = 3 * n + Sn-1
    add $t1, $t1, $t2

    # Sn = 3 * n - 2 + Sn-1
    addi $t1, $t1, -2

    # load return address and move the stack pointer back (collapse it)
    lw $ra, 0($sp)
    addi $sp, $sp, 8

    # return with the correct value of $t1
    jr $ra

base_case:

    # S = 2 when i <= 0, it then is used as the sum of all the previous series terms
    li $t1, 2

    lw $ra, 0($sp)
    addi $sp, $sp, 8

    # return 2
    jr $ra
