[bits 32]
[SECTION .text]

extern printk
extern clock_handler
extern current

global clock_handler_entry
clock_handler_entry:
    push ecx
    mov ecx, [current]
    cmp ecx, 0
    je .pop_ecx
.store_task_context:

    mov [ecx + 4 * 10], eax
    mov [ecx + 4 * 12], edx
    mov [ecx + 4 * 13], ebx
    mov [ecx + 4 * 15], ebp
    mov [ecx + 4 * 16], esi
    mov [ecx + 4 * 17], edi

    ;保存ecx
    mov eax, ecx
    pop ecx
    mov [eax + 4 * 11], ecx

    ;保存esp
    mov edx, esp
    lea edx, [edx + 4 * 3]
    mov [eax + 4 * 14], edx

    ;保存eip
    mov ecx, [esp]
    mov [eax + 4 * 8], ecx

    ;cs
    mov ecx, [esp + 4]
    mov [eax + 4 * 19], ecx

    ;eflags
    mov ecx, [esp + 8]
    mov [eax + 4 * 9], ecx

    jmp .call

.pop_ecx:
    pop ecx
.call:
    push 0x20
    call clock_handler
    add esp, 4

    iret

msg:
    db "clock_handler", 10, 0