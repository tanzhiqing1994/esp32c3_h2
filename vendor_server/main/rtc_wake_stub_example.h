/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_WAKE_UP_TIME     2

void wake_stub_example(void);
void app_sleep(void);
esp_err_t ble_mesh_init(void);
void app_main(void);

#ifdef __cplusplus
}
#endif
