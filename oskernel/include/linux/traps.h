//
// Created by ziya on 22-7-5.
//

#ifndef ZIYA_OSKERNEL_RESEARCH_TRAPS_H
#define ZIYA_OSKERNEL_RESEARCH_TRAPS_H

#include "head.h"

void gdt_init();
void idt_init();

void send_eoi(int idt_index);

#endif //ZIYA_OSKERNEL_RESEARCH_TRAPS_H
