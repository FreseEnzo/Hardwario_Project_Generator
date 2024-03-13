/*
 * Copyright (c) 2023 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */
 
/* Includes ------------------------------------------------------------------*/

#include "app_config.h"

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
                  "Set report interval (default: 3600)",
                  app_config_cmd_config_interval_report, 1, 1),

    SHELL_CMD_ARG(apn, NULL,
                  "Set APN network name",
                  app_config_cmd_config_apn, 1, 1),

    SHELL_CMD_ARG(temperature, NULL,
                  "Set Temperature 0.0f to 50.f",
                  app_config_cmd_config_temperature, 1, 1),

    SHELL_CMD_ARG(interval-aggreg, NULL,
                  "Set interval aggreg (default: 25)",
                  app_config_cmd_config_interval_aggreg, 1, 1),

    SHELL_CMD_ARG(interval-sample, NULL,
                  "Set interval aggreg (default: 25)",
                  app_config_cmd_config_interval_sample, 1, 1),

    SHELL_CMD_ARG(event-report-delay, NULL,
                  "Set event report delay (default: 1)",
                  app_config_cmd_config_event_report_delay, 1, 1),

    SHELL_CMD_ARG(event-report-rate, NULL,
                  "Set event report rate (default: 30)",
                  app_config_cmd_config_event_report_rate, 1, 1),

    SHELL_CMD_ARG(backup-report-connected, NULL,
                  "Set backup report connected (default: true)",
                  app_config_cmd_config_backup_report_connected, 1, 1),

    SHELL_CMD_ARG(backup-report-disconnected, NULL,
                  "Set backup report disconnected (default: true)",
                  app_config_cmd_config_backup_report_disconnected, 1, 1),

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
    SHELL_CMD_REGISTER(send, NULL,
                       "Set report interval (default: 3600)",
                       app_send, 1, 1);
    SHELL_CMD_REGISTER(show, NULL,
                       "Show all configs",
                       show, 1, 1);

/* USER CODE BEGIN Functions 3 */
/* USER CODE END Functions 3 */

/* clang-format on */