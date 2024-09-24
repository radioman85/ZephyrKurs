/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(selog, LOG_LEVEL_INF);

int main(void) {
    LOG_INF("Griasde %s", CONFIG_BOARD);
    
    return 0;
}
