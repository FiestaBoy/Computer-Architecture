.align 2

.data
prompt: .asciiz "Input an integer to put in the binary search tree, input 737800 to exit: "
nln: .asciiz "\n"

.text
.globl main

main:
    
    # print the prompt
    la $a0, prompt
    li $v0, 4
    syscall

    # read in the root node data
    li $v0, 5
    syscall
    move $a0, $v0

    jal new_treenode

new_treenode:

    addi $sp, $sp, -4
    sw $ra, 0($sp)

    move $s0, $a0
    
    li $v0, 9
    li $a0, 12
    syscall

    sw $s0, 0($v0)

    sw $zero, 4($v0)

    sw $zero, 8($v0)

    lw $ra, 4($v0)
    addi $sp, $sp, 4

    jr $ra
