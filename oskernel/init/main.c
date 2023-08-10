
#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/asm/system.h"
#include "../include/linux/traps.h"
#include "../include/linux/mm.h"

void test(int count, ...) {
    uint* addr = &count + count;
    unsigned int ebp_value;
    unsigned int first_param;
    __asm__("mov %0, ebp;"
            "mov %1, [ebp + 8];":"=r"(ebp_value), "=r"(first_param));
    printk("ebp value is %x\n", ebp_value);
    printk("first_param is %x\n", first_param);
    printk("%d, %d, %d", *addr, *(addr - 1), *(addr - 2));
}
void high_addr_func() {
    while(true);
}
void kernel_main(int x, short y) {
    console_init();
    printk("console initialized\n");
    gdt_init();
    printk("gdt initialized\n");
    idt_init();
    printk("idt initialized\n");
    print_check_memory_info();
    memory_init();
    memory_map_init();
//    virtual_memory_init();

    //跳转到2G虚拟地址处执行内核代码
//    __asm__("mov eax, %0;"
//            "add eax, 0x80000000;"
//            "jmp eax;"::"r"(high_addr_func));

    void* p = kmalloc(1);
    printk("0x%p\n", p);

    kfree_s(p, 1);

    kmalloc(100);
    __asm__("sti;");

    test(3, 40, 20, 10);
    while (true);

}
