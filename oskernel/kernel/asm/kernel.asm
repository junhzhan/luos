[BITS 32]

extern current
extern get_esp3
extern user_mode
[SECTION .data]
R3_CODE_SELECTOR equ (4 << 3 | 0b011)
R3_DATA_SELECTOR equ (5 << 3 | 0b011)


[SECTION .text]
;eip
;cs
;eflags
;esp3
;ss3

global move_to_user_mode
move_to_user_mode:
    xchg bx, bx
    mov esi, [current]
    push esi
    call get_esp3
    add esp, 4

    push R3_DATA_SELECTOR
    push eax
    pushf

    mov ax, R3_CODE_SELECTOR
    push eax

    push user_mode_handler

    mov ax, R3_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    iretd
user_mode_handler:
    call user_mode
    sti
    hlt