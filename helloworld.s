.align 2
.data
msg: .asciiz "hello world"

.text
.globl main # start at main label

main:
    la $a0, msg # load address
    li $v0, 4 # print string
    syscall

    li $v0, 10 # exit program function
    syscall