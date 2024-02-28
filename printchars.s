.align 2
.data

prompt: .asciiz "enter a character (~ to stop)"
string: .space 300

.text
.globl main

main:
    la $s0, string # beginning of string
    
    la $a0, prompt
    li $v0, 4
    syscall

    li $t0, 126
    addi $t1, $s0, 299 # loop guard
    # address of string + 300

read_loop:
    li $v0, 12
    syscall

    beq $v0, $t0, end_read

    sb $v0, 0($s0)
    
    bge $s0, $t1, end_read

    addi $s0, $s0, 1 # go up one byte

    b read_loop

end_read:
    sb $zero, 0($s0)

    la $s0, string # reset address

    move $a0, $s0
    li $v0, 4
    syscall

exit:
    li $v0, 10
    syscall
    