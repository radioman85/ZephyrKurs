/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

int main(void) {
    printk("Griasde %s\n", CONFIG_BOARD);
    
    return 0;
}
