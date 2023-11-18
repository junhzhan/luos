//
// Created by ziya on 22-7-1.
//
#include "../include/asm/system.h"
#include "../include/linux/kernel.h"
#include "../include/linux/mm.h"
#include "../include/string.h"

#define PDT_START_ADDR 0x20000


void* virtual_memory_init() {
    //把页表安排在1MB以下内存的地方
    int* pdt = (int*)PDT_START_ADDR;

    // 清零
    memset(pdt, 0, PAGE_SIZE);

    int ptt_count = 0;
    for (int i = 0; i < 4; ++i) {
        // pdt里面的每项，即pde，内容是ptt + 尾12位的权限位
        int ptt = (int)PDT_START_ADDR + ((i + 1) * 0x1000);
        ptt_count++;
        int pde = 0b00000000000000000000000000000111 | ptt;

        pdt[i] = pde;

        int* ptt_arr = (int*)ptt;

        if (0 == i) {
            // 第一块映射区，给内核用
            for (int j = 0; j < 0x400; ++j) {
                int* item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        } else {
            for (int j = 0; j < 0x400; ++j) {
                int* item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                virtual_addr = virtual_addr + i * 0x400 * 0x1000;

                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        }
    }
    for (int i = 512; i < 513; ++i) {
        // pdt里面的每项，即pde，内容是ptt + 尾12位的权限位
        int ptt = (int)PDT_START_ADDR + ((ptt_count + 1 + i - 512) * 0x1000);
        int pde = 0b00000000000000000000000000000111 | ptt;

        pdt[i] = pde;

        int* ptt_arr = (int*)ptt;

        if (0 == i) {
            // 第一块映射区，给内核用
            for (int j = 0; j < 0x400; ++j) {
                int* item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        } else {
            for (int j = 0; j < 0x400; ++j) {
                int* item = &ptt_arr[j];

                int virtual_addr = j * 0x1000;
                virtual_addr = virtual_addr + (i - 512) * 0x400 * 0x1000;

                *item = 0b00000000000000000000000000000111 | virtual_addr;
            }
        }
    }


    set_cr3((uint)pdt);

    enable_page();

    return pdt;
}




