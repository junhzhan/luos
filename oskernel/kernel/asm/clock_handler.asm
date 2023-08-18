[bits 32]
[SECTION .text]

extern clock_handler

extern current

; ecx
; eip
; cs
; eflags
global clock_handler_entry
clock_handler_entry:

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ebp

    push ecx
    mov ecx, [current]
    cmp ecx, 0
    je .pop_ecx

    mov [ecx + 10 * 4], eax
    mov [ecx + 12 * 4], edx
    mov [ecx + 13 * 4], ebx
    mov [ecx + 15 * 4], ebp
    mov [ecx + 16 * 4], esi
    mov [ecx + 17 * 4], edi

    mov eax, [esp + 4 * 8]          ; eip
    mov [ecx + 8 * 4], eax      ; tss.eip

    mov eax, esp
    add eax, 0x2C
    mov [ecx + 4], eax          ; tss.esp0

    mov eax, ecx
    pop ecx
    mov [eax + 11 * 4], ecx
    jmp .call_handler
.pop_ecx:
    pop ecx

.call_handler:
    push 0x20
    call clock_handler
    add esp, 4

    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    iret

msg:
    db "clock_handler", 10, 0