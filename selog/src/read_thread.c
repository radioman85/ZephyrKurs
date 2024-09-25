/*
 * Copyright (c) 2024 MyCompany
 * Author: Niklas Roth
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
LOG_MODULE_REGISTER(read_thread, LOG_LEVEL_INF);

#include "selog.h"
extern struct k_fifo se_fifo;

void read_thread_entry(void* data, void* d1, void* d2)
{
    LOG_INF("Griasde from the read thread");
    const struct device *bme = DEVICE_DT_GET(DT_NODELABEL(pres1));
    struct sensor_value temp, pres, humi;
    char buf[100];
    struct se_bme *se_bme;

    //k_sleep(K_SECONDS(3));
    while(1) {
        LOG_INF("BME says hello");
        sensor_sample_fetch(bme);
        sensor_channel_get(bme, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(bme, SENSOR_CHAN_PRESS, &pres);
        sensor_channel_get(bme, SENSOR_CHAN_HUMIDITY, &humi);
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "T: %d.%06d; P: %d.%06d; H: %d.%06d",
                        temp.val1, temp.val2,
                        pres.val1, pres.val2,
                        humi.val1, pres.val2);
        LOG_INF("%s", buf);

        se_bme = k_malloc(sizeof(struct se_bme));
        if (se_bme) {
            se_bme->temp1 = temp.val1;
            se_bme->temp2 = temp.val2;
            se_bme->humi1 = humi.val1;
            se_bme->humi2 = humi.val2;
            se_bme->pres1 = pres.val1;
            se_bme->pres2 = pres.val2;
            k_fifo_put(&se_fifo, se_bme);
        } else {
            LOG_ERR("k_malloc failed");
        }


        k_sleep(K_SECONDS(1));
    }

    LOG_INF("Pfirde from the read thread");
}