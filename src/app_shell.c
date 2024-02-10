
#include "app_config.h"


/* Zephyr includes */
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


LOG_MODULE_REGISTER(app_shell, LOG_LEVEL_INF);

/* clang-format off */

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app_config,

	SHELL_CMD_ARG(show, NULL, "List current configuration." app_config_cmd_config_show, 1, 0),

	SHELL_CMD_ARG(report-interval, NULL, "Set report interval (default: 3600)", app_config_cmd_report_interval, 1, 1),
	SHELL_CMD_ARG(counter-interval-aggreg, NULL, "Set report interval (default: 3600)", app_config_cmd_counter_interval_aggreg, 1, 1),
	SHELL_CMD_ARG(debug-mode, NULL, "Set debug mode (T/F)", app_config_cmd_debug_mode, 1, 1),
	SHELL_CMD_ARG(temperature, NULL, "Set Temperature 0.0f to 50.f", app_config_cmd_temperature, 1, 1),

SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app,

	SHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",
,print_help, 1, 0),

	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);
SHELL_CMD_REGISTER(send, NULL, 'Set report interval (default: 3600)', 'app_send');
SHELL_CMD_REGISTER(show, NULL, 'Show all configs', 'show');

/* clang-format on */
