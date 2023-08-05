
#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/asm/io.h"
#include "../include/asm/system.h"

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
void kernel_main(int x, short y) {
    console_init();
    char* s = "ziya";
    printk("name: %s\n", s);
    printk("name: %s\n", s);

    BOCHS_DEBUG_MAGIC
//    out_byte(0x3D4, 0xc);
//    uchar v1 = in_byte(0x3D5);
//    out_byte(0x3D4, 0xd);
//    uchar v2 = in_byte(0x3D5);
//    out_byte(0x3D4, 0xc);
//    out_byte(0x3D5, 0);
//    out_byte(0x3D4, 0xd);
//    out_byte(0x3D5, 0);
//    u8* p = (u8*)0xb8003;
//    *p = 0xce;
    test(3, 40, 20, 10);
    while (true);

}