/* net_thread.c: network thread
 *
 * Copyright (c) 2022, 2023 Andreas Klinger
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/net/socket.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(net_thread, LOG_LEVEL_INF);

#include "selog.h"

#define RECV_BUF_SIZE 128
#define PEER_PORT	2000


extern struct k_fifo se_fifo;

// extern int net_running;
int net_running = 1;

int sock_fd = -1;

K_SEM_DEFINE(run_app, 0, 1);

static ssize_t sendall(int sock, const void *buf, size_t len)
{
	while (len) {
		ssize_t out_len = send(sock, buf, len, 0);
		if (out_len < 0)
			return out_len;
		buf = (const char *)buf + out_len;
		len -= out_len;
	}

	return 0;
}

static int start_tcp(void)
{
	int ret;
	struct sockaddr_in addr4;

	addr4.sin_family = AF_INET;
	addr4.sin_port = htons(PEER_PORT);
	inet_pton(AF_INET, CONFIG_NET_CONFIG_PEER_IPV4_ADDR, &addr4.sin_addr);

	sock_fd = socket(addr4.sin_family, SOCK_STREAM, IPPROTO_TCP);
	if (sock_fd < 0) {
		LOG_ERR("Failed to create TCP socket: %d", errno);
		return -errno;
	}

	ret = connect(sock_fd, (struct sockaddr *)&addr4, sizeof(addr4));
	if (ret < 0) {
		LOG_ERR("Cannot connect to TCP remote: %d", errno);
		ret = -errno;
	}

	return ret;
}

static void stop_tcp(void)
{
	if (sock_fd >= 0)
		close(sock_fd);
	sock_fd = -1;
}

static int process_tcp(void)
{
	int ret, retry = 1;
	char buf[RECV_BUF_SIZE];
	struct se_bme *se_bme;

	do {
		se_bme = k_fifo_get(&se_fifo, K_FOREVER);
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "T: %d.%06d; P: %d.%06d; H: %d.%06d",
                        se_bme->temp1, se_bme->temp2,
                        se_bme->pres1, se_bme->pres2,
                        se_bme->humi1, se_bme->humi2);
		k_free(se_bme);

		ret =  sendall(sock_fd, buf, strlen(buf));
		if (ret < 0) {
			LOG_ERR("TCP: Failed to send data, errno %d", errno);
			stop_tcp();
			start_tcp();
		} else
			LOG_DBG("TCP: Sent %d bytes", strlen(buf));

	} while (retry-- > 0);

	return ret;
}

void net_thread_entry(void *data, void *d1, void *d2)
{
	int ret = 0;

	LOG_INF("Servus from the net thread");

	if (!IS_ENABLED(CONFIG_NET_IPV4)) {
		LOG_ERR("IPV4 not enabled");
		net_running = 0;
		return;
	}

	start_tcp();

	while (net_running) {
		ret = process_tcp();
	}

	stop_tcp();

	LOG_INF("Bye-bye from the net thread with %d", ret);
}

