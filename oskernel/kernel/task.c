

#include "../include/linux/task.h"
#include "../include/linux/kernel.h"
#include "../include/string.h"

task_t* tasks[NR_TASKS] = {0};


static int find_empty_process() {
    int ret = 0;
    bool is_finded = false;
    for (int i = 0; i < NR_TASKS;i++) {
        if (tasks[i] == 0) {
            is_finded = true;
            ret = i;
            break;
        }
    }
    if (!is_finded) {
        printk("no valid pid\n");
        return -1;
    }
    return ret;
}


task_t* create_task(char* name, task_fun_t fun) {
    task_t* task = kmalloc(4096);
    task->state = TASK_INIT;
    task->esp0 = (int)task + 0x1000;
    task->pid = find_empty_process();
    task->ppid = 0;
    task->function = fun;
    tasks[task->pid] = task;
    memcpy(task->name, name, strlen(name));
    task->state = TASK_READY;
    return task;
}

void* idle(void* arg) {
    for(int i = 0;i < 1000;i++) {
        printk("idle: %d\n", i);
    }
}

task_fun_t get_task_function(task_t* task) {
    return task->function;
}

void task_init() {
    create_task("idle", idle);
}