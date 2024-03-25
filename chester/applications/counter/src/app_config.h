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
struct app_config {
	int interval_sample;
	int interval_report;
	int event_report_delay;
	int event_report_rate;
	bool backup_report_connected;
	bool backup_report_disconnected;

	/* USER CODE BEGIN Struct Variables */
	/* USER CODE END Struct Variables */
};

extern struct app_config g_app_config;

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_interval_sample(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_interval_report(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_event_report_delay(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_event_report_rate(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_backup_report_connected(const struct shell *shell, size_t argc,
						  char **argv);
int app_config_cmd_config_backup_report_disconnected(const struct shell *shell, size_t argc,
						     char **argv);

/* USER CODE BEGIN Functions 1 */
/* USER CODE END Functions 1 */

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */