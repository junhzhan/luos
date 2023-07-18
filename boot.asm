[ORG 0x7c00]

BOOT_MAIN_ADDR equ 0x500

[SECTION .text]
[BITS 16]
global _start
_start:

        ; 设置屏幕模式为文本模式，清除屏幕
    mov ax, 3
    int 0x10

    mov di, BOOT_MAIN_ADDR
    mov ecx, 1
    mov bl, 2
    call read_hd

    mov si, jmp_to_setup
    call print
    jmp    BOOT_MAIN_ADDR


read_hd:
    xchg bx, bx
    mov dx, 0x1f2
    mov al, bl;bl=2
    out dx, al

    inc dx;dx=0x1f3
    mov al, cl
    out dx, al

    inc dx;dx=0x1f4
    mov al, ch
    out dx, al

    inc dx;dx=0x1f5
    shr ecx, 16
    mov al, cl
    out dx, al

    inc dx
    shr ecx, 8
    and cl, 0b1111
    mov al, 0b1110_0000     ; LBA模式
    or al, cl
    out dx, al


    inc dx;dx=0xf17
    mov al, 0x20
    out dx, al

    mov cl, bl

.start_read:
    push cx
    call .wait_hd_prepare
    call read_hd_data
    pop cx
    loop .start_read
.return:
    ret

.wait_hd_prepare:
    mov dx, 0x1f7
.check:
    in al, dx
    and al, 0b1000_1000
    cmp al, 0b0000_1000
    jnz .check
    ret

read_hd_data:
    mov dx, 0x1f0
    mov cx, 256
.read_word:
    in ax, dx
    mov [di], ax
    add di, 2
    loop .read_word

    ret

; 如何调用
; mov     si, msg   ; 1 传入字符串
; call    print     ; 2 调用
print:
    mov ah, 0x0e
    mov bh, 0
    mov bl, 0x0c
.loop:
    mov al, [si]
    cmp al, 0
    jz .done
    int 0x10

    inc si
    jmp .loop
.done:
    ret

jmp_to_setup:
    db "jump to setup...", 10, 13, 0

times 510 - ($ - $$) db 0
db 0x55, 0xaa
