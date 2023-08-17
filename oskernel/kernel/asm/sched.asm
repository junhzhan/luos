[BITS 32]
[SECTION .text]
extern current
extern get_task_ppid
extern inc_scheduling_times
extern task_exit
extern sched

;切idle任务专用
global switch_idle_task
switch_idle_task:
    ;恢复上下文
    mov eax, [current]
    mov esp, [eax + 4]
    mov ebp, [eax + 15 * 4]

    mov ecx, [eax + 11 * 4]
    mov edx, [eax + 12 * 4]
    mov ebx, [eax + 13 * 4]
    mov esi, [eax + 16 * 4]
    mov edi, [eax + 17 * 4]

    mov eax, [eax + 8 * 4]

    sti
    jmp eax

    sti
    hlt

global switch_task
switch_task:
    ;恢复上下文
    mov eax, [current]

    ;恢复ebp0 esp0
    mov esp, [eax + 4]
    mov ebp, [eax + 15 * 4]

    push eax
    call get_task_ppid
    add esp, 4
    cmp eax, 0
    jne .recover_env

    mov eax, [current]
    push eax
    call inc_scheduling_times
    add esp, 4

    cmp eax, 0
    jne .recover_env

    mov eax, task_exit_handler
    push eax
.recover_env:
    mov eax, [current]

    ;恢复通用寄存器
    mov ecx, [eax + 11 * 4]
    mov edx, [eax + 12 * 4]
    mov ebx, [eax + 13 * 4]
    mov esi, [eax + 16 * 4]
    mov edi, [eax + 17 * 4]

    mov eax, [eax + 8 * 4]

    sti
    jmp eax

task_exit_handler:
    mov eax, [current]
    push eax
    push 0
    call task_exit
    add esp, 8
    call sched

    sti
    hlt
