/*
 * Copyright (c) 2024 HARDWARIO a.s.
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
	enum app_config_mode mode;
	int interval_sample;
	float hygro_t_alarm_hi_thr;
	char apn [9];
		
	bool hygro_t_alarm_lo_report;
	bool channel_differential[4];
	int channel_calib_x0[4];

	/* USER CODE BEGIN Struct Variables */
	/* USER CODE END Struct Variables */
};

extern struct app_config g_app_config;

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
int app_config_cmd_config_mode(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_interval_sample(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_hygro_t_alarm_hi_thr(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_hygro_t_alarm_lo_report(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_differential(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_calib_x0(const struct shell *shell, size_t argc, char **argv);

/* USER CODE BEGIN Functions 1 */
/* USER CODE END Functions 1 */

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */