/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>
#include <zephyr/random/random.h>
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

//=====================================================================================================
//static k_tid_t* _read_tid_p;

//int set_thread(k_tid_t* read_tid_p)
//{
//    _read_tid_p = read_tid_p;
//}

extern k_tid_t read_tid;

static int cmd_selog_suspend(const struct shell *shell, size_t argc, char **argv)
{
    k_thread_suspend(read_tid);
    shell_print(shell, "Suspend Thread");

    return 0;
}

static int cmd_selog_resume(const struct shell *shell, size_t argc, char **argv)
{
    k_thread_resume(read_tid);
    shell_print(shell, "Resume Thread");

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_selog, 
    SHELL_CMD(suspend, NULL, "...Suspend", cmd_selog_suspend),
    SHELL_CMD(resume, NULL, "Resume...", cmd_selog_resume),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(selog, &sub_selog, "Controlling selog system", NULL);