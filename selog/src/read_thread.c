/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(read_thread, LOG_LEVEL_INF);

void read_thread_entry(void* data, void* d1, void* d2)
{
    LOG_INF("Griasde from the read thread");

    //k_sleep(K_SECONDS(3));
    while(1) {
        LOG_INF("Heeeeello World");
        k_sleep(K_SECONDS(3));
    }

    LOG_INF("Pfirde from the read thread");
}