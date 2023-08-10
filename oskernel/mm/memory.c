

#include "../include/linux/mm.h"
#include "../include/linux/kernel.h"
#include "../include/string.h"

#define ARDS_ADDR 0x1100
#define LOW_MEM 0x100000 //1M以下的物理内存给内核用

#define ZONE_VALID 1
#define ZONE_RESERVED 2

#define VALID_MEMORY_FROM 0x100000

physics_memory_info_t g_physics_memory;
physics_memory_map_t g_physics_memory_map;

void print_check_memory_info() {
    check_memory_info_t* p = (check_memory_info_t*)ARDS_ADDR;
    check_memmory_item_t* p_data = (check_memmory_item_t*)(ARDS_ADDR + 2);
    unsigned short times = p->times;
    for (int i = 0; i < times;i++) {
        check_memmory_item_t* tmp = p_data + i;
        printk("%x, %x, %x, %x, %d\n", tmp->base_addr_high, tmp->base_addr_low, tmp->length_high, tmp->length_low, tmp->type);
    }
}

void memory_init() {
    check_memory_info_t* p = (check_memory_info_t*)ARDS_ADDR;
    check_memmory_item_t* p_data = (check_memmory_item_t*)(ARDS_ADDR + 2);
    for (int i = 0;i < p->times;i++) {
        check_memmory_item_t* tmp = p_data + i;
        if (tmp->base_addr_low > 0 && tmp->type == ZONE_VALID) {
            g_physics_memory.addr_start = tmp->base_addr_low;
            g_physics_memory.valid_mem_size = tmp->length_low;
            g_physics_memory.addr_end = tmp->base_addr_low + tmp->length_low;
        }
    }

    if (VALID_MEMORY_FROM != g_physics_memory.addr_start) {
        printk("[%s:%d] no valid physics memory\n", __FILE__, __LINE__);
        return;
    }
    g_physics_memory.pages_total = g_physics_memory.valid_mem_size / PAGE_SIZE;
    printk("pages total is %x\n", g_physics_memory.pages_total);
    uint left_size = g_physics_memory.valid_mem_size % PAGE_SIZE;
    printk("memory size smaller than PAGE_SIZE is %d\n", left_size);
    g_physics_memory.pages_used = 0;
    g_physics_memory.pages_free = g_physics_memory.pages_total - g_physics_memory.pages_used;
}


void memory_map_init() {
    if (VALID_MEMORY_FROM != g_physics_memory.addr_start) {
        printk("[%s:%d] no valid physics memory\n", __FILE__, __LINE__);
        return;
    }
    g_physics_memory_map.addr_base = VALID_MEMORY_FROM;
    g_physics_memory_map.map = (uchar*)0x10000;

    g_physics_memory_map.pages_total = g_physics_memory.pages_total;

    memset(g_physics_memory_map.map, 0, g_physics_memory_map.pages_total);
}

void* get_free_page() {
    bool find = false;
    int i = g_physics_memory_map.bitmap_item_used;
    for (;i < g_physics_memory_map.pages_total;i++) {
        if (g_physics_memory_map.map[i] == 0) {
            find = true;
            break;
        }
    }
    if (!find) {
        printk("memory used up!");
        return NULL;
    }
    g_physics_memory_map.map[i] = 1;
    g_physics_memory_map.bitmap_item_used++;

    void* ret = (void*)(g_physics_memory_map.addr_base + (i << 12));
    printk("[%s]return: 0x%x, used: %d pages\n", __FUNCTION__ , ret, g_physics_memory_map.bitmap_item_used);
    return ret;
}

void free_page(void* p) {
    if (p < g_physics_memory.addr_start || p > g_physics_memory.addr_end) {
        printk("invalid address!");
        return;
    }
    int i = ((int)p - g_physics_memory_map.addr_base) >> 12;
    g_physics_memory_map.map[i] = 0;
    g_physics_memory_map.bitmap_item_used--;
    printk("[%s]return: 0x%x, used: %d pages\n", __FUNCTION__ , p, g_physics_memory_map.bitmap_item_used);
}