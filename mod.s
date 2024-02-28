.align 2

.data
msg1: .asciiz "this function returns int1 % int2, enter int1: "
msg2: .asciiz "enter int2: "
msg3: .asciiz "result: "
nln: .asciiz "\n"

.text
.globl main

main: 

    # print msg1
    la $a0, msg1
    li $v0, 4
    syscall

    # take in int1
    li $v0, 5
    syscall
    move $t0, $v0

    # print new line
    la $a0, nln
    li $v0, 4
    syscall

    # print msg2
    la $a0, msg2
    li $v0, 4
    syscall

    # take in int2
    li $v0, 5
    syscall
    move $t1, $v0

    # print new line
    la $a0, nln
    li $v0, 4
    syscall

    # FOR DIVISION
    # li $t2, 0

loop:

    # exit and print the result if int1 < int2
    blt $t0, $t1, exit

    # subtract int2 from int1
    sub $t0, $t0, $t1

    # FOR DIVISION
    # increment the counter
    #addi $t2, $t2, 1

    # loop again
    j loop

exit:
    # print msg3
    la $a0, msg3
    li $v0, 4
    syscall

    # print remainder
    move $a0, $t0
    li $v0, 1
    syscall

    # exit
    li $v0, 10
    syscall

