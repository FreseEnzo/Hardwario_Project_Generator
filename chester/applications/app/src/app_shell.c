/*
 * Copyright (c) 2024 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */

/* Includes ------------------------------------------------------------------*/
#include "app_config.h"
#include "app_work.h"

/* Private includes --------------------------------------------------------------------*/

/* Zephyr includes */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <errno.h>
#include <stdlib.h>

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

LOG_MODULE_REGISTER(app_shell, LOG_LEVEL_INF);

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

static int cmd_sample(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "unknown parameter: %s", argv[1]);
		shell_help(shell);
		return -EINVAL;
	}

	app_work_sample();

	return 0;
}

static int cmd_send(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "unknown parameter: %s", argv[1]);
		shell_help(shell);
		return -EINVAL;
	}

	app_work_send();

	return 0;
}

static int cmd_aggreg(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "unknown parameter: %s", argv[1]);
		shell_help(shell);
		return -EINVAL;
	}

	app_work_aggreg();

	return 0;
}

static int print_help(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "command not found: %s", argv[1]);
		shell_help(shell);
		return -EINVAL;
	}

	shell_help(shell);
	return 0;
}

/* clang-format off */

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app_config,
   
	SHELL_CMD_ARG(show, NULL,
				  "List current configuration.",
				  app_config_cmd_config_show, 1, 0),
	
	SHELL_CMD_ARG(mode, NULL,
				  "Get/Set communication mode (None/LTE/LoRaWAN) ('none', 'lte', 'lrw').",
				  app_config_cmd_config_mode, 1, 1),
	SHELL_CMD_ARG(interval_sample, NULL,
				  "Get/Set sample interval in seconds (format: <1-86400>).",
				  app_config_cmd_config_interval_sample, 1, 1),
	
	SHELL_CMD_ARG(hygro-t-alarm-hi-thr, NULL,
				  "Get/Set hygro high temperature alarm threshold (format: <-40.0..125.0>).",
				  app_config_cmd_config_hygro_t_alarm_hi_thr, 1, 1),
	
	SHELL_CMD_ARG(apn, NULL,
				  "Set APN network name",
				  app_config_cmd_config_apn, 1, 1),
	
	SHELL_CMD_ARG(hygro-t-alarm-lo-report, NULL,
				  "Get/Set report when hygro low temperature alarm is crossed (format: true, false).",
				  app_config_cmd_config_hygro_t_alarm_lo_report, 1, 1),
	
	SHELL_CMD_ARG(channel-differential, NULL,
				"Get/Set channel differential mode (format: <channel> <true|false>).",
				app_config_cmd_config_channel_differential, 2, 1),
	
	SHELL_CMD_ARG(channel-calib-x0, NULL,
				"Get/Set channel X0 calibration point (format: <channel> <-2147483648..2147483647>).",
				app_config_cmd_config_channel_calib_x0, 2, 1),
	
	/* USER CODE BEGIN Functions 1 */
	/* USER CODE END Functions 1 */

	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app,

	SHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",
				  print_help, 1, 0),
		
	SHELL_SUBCMD_SET_END

/* USER CODE BEGIN Functions 2 */
/* USER CODE END Functions 2 */

);

SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);

SHELL_CMD_REGISTER(sample, NULL,"Sample immediately.", cmd_sample);
SHELL_CMD_REGISTER(send, NULL,"Send data immediately.", cmd_send);
SHELL_CMD_REGISTER(aggreg, NULL,"Aggregate data immediately", cmd_aggreg);

/* USER CODE BEGIN Functions 3 */
/* USER CODE END Functions 3 */

/* clang-format on */