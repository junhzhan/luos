
#ifndef ZIYA_OSKERNEL_RESEARCH_TASK_H
#define ZIYA_OSKERNEL_RESEARCH_TASK_H

#include "types.h"
#include "mm.h"

#define NR_TASKS 64

typedef enum task_state_t {
    TASK_INIT,     // 初始化
    TASK_RUNNING,  // 执行
    TASK_READY,    // 就绪
    TASK_BLOCKED,  // 阻塞
    TASK_SLEEPING, // 睡眠
    TASK_WAITING,  // 等待
    TASK_DIED,     // 死亡
} task_state_t;

typedef void* (*task_fun_t)(void*);
typedef struct tss_t {
    u32 backlink; // 前一个任务的链接，保存了前一个任状态段的段选择子
    u32 esp0;     // ring0 的栈顶地址
    u32 ss0;      // ring0 的栈段选择子
    u32 esp1;     // ring1 的栈顶地址
    u32 ss1;      // ring1 的栈段选择子
    u32 esp2;     // ring2 的栈顶地址
    u32 ss2;      // ring2 的栈段选择子
    u32 cr3;
    u32 eip;
    u32 flags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es;
    u32 cs;
    u32 ss;
    u32 ds;
    u32 fs;
    u32 gs;
    u32 ldtr;          // 局部描述符选择子
    u16 trace : 1;     // 如果置位，任务切换时将引发一个调试异常
    u16 reversed : 15; // 保留不用
    u16 iobase;        // I/O 位图基地址，16 位从 TSS 到 IO 权限位图的偏移
    u32 ssp;           // 任务影子栈指针
} __attribute__((packed)) tss_t;

typedef struct task_t {
    tss_t context;
    char name[16];
    int pid;
    int ppid;
    int cr3;
    task_state_t state;
    int esp0;
    task_fun_t function;
}__attribute((packed)) task_t;

typedef union task_union_t {
    task_t task;
    char stack[PAGE_SIZE];
}task_union_t;

task_t* create_task(char* name, task_fun_t fun);

void task_init();

#endif