/*
 * Copyright (c) 2022, The Puppy RTOS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include <puppy.h>

struct _thread_obj t1;
__attribute__((aligned(8)))
uint8_t t1_thread_stack[1024];

void t1_thread_entry(void *parm)
{
    while(1)
    {
        printk("t1:%d\r\n", p_tick_get());
        p_thread_sleep(100);
    }
}

int main(void)
{
    int board_init(void);
    board_init();
    printk("Hello Puppy!\r\n");
    p_thread_init(&t1, "idle", t1_thread_entry, NULL,
                  t1_thread_stack,
                  sizeof(t1_thread_stack),
                  12);
    p_thread_start(&t1);
}

