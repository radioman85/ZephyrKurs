/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(bme280_thread, LOG_LEVEL_INF);

void bme280_thread_entry(void* data, void* d1, void* d2)
{
    LOG_INF("I am the bme280 thread");

    //k_sleep(K_SECONDS(3));
    while(1) {
        LOG_INF("BME says hello");
        k_sleep(K_SECONDS(6));
    }

    LOG_INF("bme280 thread stopped");
}