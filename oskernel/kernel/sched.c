#include "../include/linux/task.h"
#include "../include/linux/kernel.h"

extern task_t* tasks[NR_TASKS];
extern void switch_task(task_t* next);

task_t* current = NULL;


task_t* find_ready_task() {
    task_t* next = NULL;

    for (int i = 0; i < NR_TASKS; ++i) {
        task_t* task = tasks[i];

        if (NULL == task) continue;
        if (TASK_READY != task->state) continue;

        next = task;
        break;
    }

    return next;
}

void sched() {
    task_t* next = find_ready_task();

    if (NULL == next) {
        printk("no task found\n");
        return;
    }

//    next->state = TASK_RUNNING;

    current = next;

    switch_task(next);
}