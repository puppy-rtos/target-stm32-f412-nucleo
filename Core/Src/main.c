/*
 * Copyright (c) 2022, The Puppy RTOS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include <puppy.h>


struct _thread_obj t1;
__attribute__((aligned(8)))
uint8_t thread_stack[1024];

struct _thread_obj idle;
__attribute__((aligned(8)))
uint8_t idle_thread_stack[1024];


struct _thread_obj main_t;
__attribute__((aligned(8)))
uint8_t thread2_stack[1024];

extern void _thread_init(p_obj_t obj, const char *name,
                                void (*entry)(void *param),
                                void    *param,
                                void    *stack_addr,
                                uint32_t stack_size,
                                uint8_t  prio);

void t1_entry(void *parm)
{ 
    while(1)
    {
        p_sched_lock();
        printk("t1:%d\r\n", p_tick_get());
        p_sched_unlock();
    }
}
void main_entry(void *parm)
{
    _thread_init(&idle, "idle", t1_entry, 0, idle_thread_stack, sizeof(idle_thread_stack), 31);
    _thread_init(&t1, "t1", t1_entry, 0, thread_stack, sizeof(thread_stack), 13);
    p_thread_start(&t1);
    p_thread_start(&idle);

    while(1)
    {
        p_sched_lock();
        printk("hello I'm in thread main,%d\r\n", p_tick_get());
        p_sched_unlock();
        p_thread_sleep(200);
    }

    printk("thread main will exit,%d\r\n", p_tick_get());

}
void idle_entry(void *parm)
{
    while(1)
    {

    }
}

int main(void)
{
    int board_init(void);
    board_init();

    // kobj_tc_main();
    // test_atomic_api();

    _thread_init(&main_t, "main", main_entry, 0, thread2_stack, sizeof(thread2_stack), 12);
    p_thread_start(&main_t);
    while (1);
}

