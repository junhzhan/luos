

#include "../include/asm/io.h"


#define PIC_M_CTRL 0x20
#define PIC_S_CTRL 0xA0
#define PIC_EOI 0x20

void send_eoi(int idt_index) {

    if (idt_index >= 0x20 && idt_index < 0x28) {
        out_byte(PIC_M_CTRL, PIC_EOI);
    } else if (idt_index >= 0x28 && idt_index < 0x30) {
        out_byte(PIC_M_CTRL, PIC_EOI);
        out_byte(PIC_S_CTRL, PIC_EOI);
    }
}