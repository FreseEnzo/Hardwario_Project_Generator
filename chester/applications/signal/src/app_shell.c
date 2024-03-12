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

    

    SHELL_CMD_ARG(measurement-interval, NULL,
                  "Set measurement interval (default: 60)",
                  app_config_cmd_config_measurement_interval, 1, 1),

    SHELL_CMD_ARG(report-interval, NULL,
                  "Set measurement interval (default: 300)",
                  app_config_cmd_config_report_interval, 1, 1),

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

/* USER CODE BEGIN Functions 3 */
/* USER CODE END Functions 3 */

/* clang-format on */