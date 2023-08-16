[SECTION .data]
msg:
    db "hello", 10, 13, 0

[SECTION .text]
[BITS 32]

extern printk
extern get_task_function
extern current
global switch_task
switch_task:
    mov eax, [current]
    push eax
    call get_task_function
    add esp, 4
    sti
    call eax
    ret