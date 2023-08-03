[SECTION .text]
[BITS 32]
extern kernel_main

global _start

_start:
    mov ax, -3
    push ax
    push 2;此处会压入4个字节的数据,因为CPU处于32位模式,如果用push ax，则会压入2个字节的数据
    call kernel_main
    jmp $