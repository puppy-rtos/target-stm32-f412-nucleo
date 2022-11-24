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


struct _thread_obj t2;
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
//        p_thread_sleep(200);
        // p_thread_yield();
    }
}
void t2_entry(void *parm)
{
    p_obj_t thread1 = p_obj_find("t1");
    p_thread_start(thread1);

    while(1)
    {
        p_sched_lock();
        printk("hello I'm in thread t2,%d\r\n", p_tick_get());
        p_sched_unlock();
        p_thread_sleep(200);
    }
    // p_thread_yield();
    printk("thread t2 will exit,%d\r\n", p_tick_get());

}
void thread_init_tc(void)
{
    _thread_init(&t1, "t1", t1_entry, 0, thread_stack, sizeof(thread_stack), 13);
    _thread_init(&t2, "t2", t2_entry, 0, thread2_stack, sizeof(thread2_stack), 12);
    p_thread_start(&t2);
}


int main(void)
{
    int board_init(void);
    board_init();

    // kobj_tc_main();
    // test_atomic_api();
    thread_init_tc();

    while (1)
    {
        printk("tick:%d\r\n", p_tick_get());
        HAL_Delay(1000);
    }
}

