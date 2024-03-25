/*
 * Copyright (c) 2023 HARDWARIO a.s.
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
    
    SHELL_CMD_ARG(interval-report, NULL,
                  "Get/Set report interval in seconds (format: <30-86400>).",
                  app_config_cmd_config_interval_report, 1, 1),
    
    SHELL_CMD_ARG(event-report-delay, NULL,
                  "Get/Set event report delay in seconds (format: <1-86400>).",
                  app_config_cmd_config_event_report_delay, 1, 1),
    
    SHELL_CMD_ARG(event-report-rate, NULL,
                  "Get/Set event report rate in reports per hour (format: <1-3600>).",
                  app_config_cmd_config_event_report_rate, 1, 1),
    
    SHELL_CMD_ARG(backup-report-connected, NULL,
                  "Set backup report connected (default: true)",
                  app_config_cmd_config_backup_report_connected, 1, 1),
    
    SHELL_CMD_ARG(backup-report-disconnected, NULL,
                  "Set backup report disconnected",
                  app_config_cmd_config_backup_report_disconnected, 1, 1),
    
    SHELL_CMD_ARG(trigger-active-duration, NULL,
                  "Get/Set event active duration in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_trigger_duration_active, 1, 1),
    
    SHELL_CMD_ARG(trigger-inactive-duration, NULL,
                  "Get/Set event inactive duration in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_trigger_duration_inactive, 1, 1),
    
    SHELL_CMD_ARG(trigger-cooldown-time, NULL,
                  "Get/Set trigger cooldown time in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_trigger_cooldown_time, 1, 1),
    
    SHELL_CMD_ARG(trigger-report-active, NULL,
                  "Set report when trigger is active",
                  app_config_cmd_config_trigger_report_active, 1, 1),
    
    SHELL_CMD_ARG(trigger-report-inactive, NULL,
                  "Set report when trigger is inactive",
                  app_config_cmd_config_trigger_report_inactive, 1, 1),
    
    SHELL_CMD_ARG(counter-interval-aggreg, NULL,
                  "Get/Set counter aggregation interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_counter_interval_aggreg, 1, 1),
    
    SHELL_CMD_ARG(counter-duration-active, NULL,
                  "Get/Set event active duration in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_counter_duration_active, 1, 1),
    
    SHELL_CMD_ARG(counter-duration-inactive, NULL,
                  "Get/Set event inactive duration in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_counter_duration_inactive, 1, 1),
    
    SHELL_CMD_ARG(counter-cooldown-time, NULL,
                  "Get/Set counter cooldown time in milliseconds (format: <0-60000>).",
                  app_config_cmd_config_counter_cooldown_time, 1, 1),
    
    SHELL_CMD_ARG(analog-interval-sample, NULL,
                  "Get/Set analog sample interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_analog_interval_sample, 1, 1),
    
    SHELL_CMD_ARG(analog-interval-aggreg, NULL,
                  "Get/Set analog aggregation interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_analog_interval_aggreg, 1, 1),
    
    SHELL_CMD_ARG(hygro-interval-sample, NULL,
                  "Get/Set hygro sample interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_hygro_interval_sample, 1, 1),
    
    SHELL_CMD_ARG(hygro-interval-aggreg, NULL,
                  "Get/Set hygro aggreg interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_hygro_interval_aggreg, 1, 1),
    
    SHELL_CMD_ARG(w1-therm-interval-sample, NULL,
                  "Get/Set ds18b20 sample interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_w1_therm_interval_sample, 1, 1),
    
    SHELL_CMD_ARG(w1-therm-interval-aggreg, NULL,
                  "Get/Set ds18b20 aggregation interval in seconds (format: <1-86400>).",
                  app_config_cmd_config_w1_therm_interval_aggreg, 1, 1),
    
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