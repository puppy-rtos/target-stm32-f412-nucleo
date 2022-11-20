/*
 * Copyright (c) 2022, The Puppy RTOS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include <puppy.h>

int main(void)
{
    int board_init(void);
    board_init();

    // kobj_tc_main();

    while (1)
    {
        printk("tick:%d\r\n", HAL_GetTick());
        HAL_Delay(1000);
    }
}
