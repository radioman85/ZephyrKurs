/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SELOG_H
#define _SELOG_H

#include <stdint.h>

struct se_bme {
    void    *reserved;
    int32_t temp1;
    int32_t temp2;
    int32_t humi1;
    int32_t humi2;
    int32_t pres1;
    int32_t pres2;
};

#endif /* _SELOG_H */