/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(selog, LOG_LEVEL_INF);

extern void read_thread_entry(void* data, void* d1, void* d2);

#define READ_STACK_SIZE 500
#define READ_PRIORITY -5

K_KERNEL_STACK_DEFINE(read_stack_area, READ_STACK_SIZE);

int main(void) 
{
    int ret;
    struct k_thread read_thread_ctl;
    k_tid_t read_tid;

    LOG_INF("Griasde from %s", CONFIG_BOARD);

    read_tid = k_thread_create(&read_thread_ctl, read_stack_area, 
                    K_KERNEL_STACK_SIZEOF(read_stack_area),
                    read_thread_entry,
                    NULL, NULL, NULL,
                    READ_PRIORITY, 0, K_NO_WAIT);

    if (read_tid != &read_thread_ctl) {
        LOG_ERR("Error while creating a thread: %d", (int)read_tid);
        return 1;
    }

    ret = k_thread_name_set(read_tid, "read_thread");
    if (ret)
        LOG_ERR("Error while creating a thread: %d", (int)read_tid);

    ret = k_thread_join(read_tid, K_FOREVER);
    if(!ret)
        LOG_DBG("Read thread terminated");
    else
        LOG_ERR("Error while terminating read thread: %d", ret);

    LOG_INF("Servus");

    return 0;
}
