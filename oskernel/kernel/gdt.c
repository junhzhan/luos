
#include "../include/linux/types.h"
#include "../include/linux/head.h"
#include "../include/linux/kernel.h"
#include "../include/string.h"



#define GDT_SIZE 128

u64 gdt[GDT_SIZE] = {0};
xdt_ptr_t gdt_ptr;

int r3_code_selector;
int r3_data_selector;


void gdt_init() {
    printk("init gdt...\n");
    __asm__("sgdt gdt_ptr;");
    memcpy(gdt, (void*)gdt_ptr.base, gdt_ptr.limit);
    gdt_ptr.base = (int)gdt;
    gdt_ptr.limit = sizeof(gdt) - 1;
    __asm__("lgdt gdt_ptr;");
}




