/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(shell, LOG_LEVEL_INF);

static int cmd_print_random(const struct shell *shell, size_t argc, char **argv)
{
    int cnt = 1;
    int i;
    char c;

    shell_print(shell, "START RANDOM:");

    if (argc >= 2)
        cnt = atoi(argv[1]);

    for (i = 0; i < cnt; i++) {
        sys_rand_get(&c, 1);
        shell_print(shell, "0x%02X", c);
    }

    shell_print(shell, ":END");

    return 0;    
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_print, 
    SHELL_CMD(random, NULL, "<bytes> Print random hex bytes.", cmd_print_random),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(print, &sub_print, "Print system information", NULL);