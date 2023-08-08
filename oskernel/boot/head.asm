[SECTION .text]
[BITS 32]
extern kernel_main

global _start

_start:

.config_8259a:
    ;发送ICW1寄存器的值
    mov al, 11h
    out 20h, al

    out 0A0h, al

    mov al, 20h
    out 21h, al

    mov al, 28h
    out 0A1h, al

    mov al, 04h
    out 21h, al
    mov al, 02h
    out 0a1h, al

    mov al, 03h
    out 21h, al
    out 0a1h, al

.enable_intr:
    mov al, 11111111b
    out 21h, al

    mov al, 11111111b
    out 0A1h, al

.enter_c_world:
    mov ax, -3
    push ax
    push 2;此处会压入4个字节的数据,因为CPU处于32位模式,如果用push ax，则会压入2个字节的数据
    call kernel_main
    jmp $