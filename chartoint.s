.align 2

.data 
msg: .asciiz "input a character: " 
nln: .asciiz "\n"

.text

.globl main

main:
    la $a0, msg
    li $v0, 4
    syscall

    li $v0, 12
    syscall

    move $t0, $v0

    la $a0, nln
    li $v0, 4
    syscall

    move $a0, $t0

    li $v0, 1
    syscall

    li $v0, 10
    syscall