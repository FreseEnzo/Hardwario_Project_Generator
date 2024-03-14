/*
 * Copyright (c) 2023 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* Includes ------------------------------------------------------------------*/

/* Private includes --------------------------------------------------------------------*/

/* Zephyr includes */
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <stdbool.h>
#include <stddef.h>

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

#ifdef __cplusplus
extern "C" {
#endif

/* Private Variables -------------------------------------------------------------------*/

enum app_config_mode {
	APP_CONFIG_MODE_NONE = 0,
	APP_CONFIG_MODE_LTE = 1,
	APP_CONFIG_MODE_LRW = 2,
};

struct app_config {
    int measurement_interval;
    int report_interval;
};

extern struct app_config g_app_config;

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_measurement_interval(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_report_interval(const struct shell *shell, size_t argc, char **argv);

/* USER CODE BEGIN Functions 1 */
/* USER CODE END Functions 1 */

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */