
#include "app_config.h"
#include "app_work.h"


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
SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app_config,

	SHELL_CMD_ARG(show, NULL, "List current configuration." app_config_cmd_config_show, 1, 0),
	SHELL_CMD_ARG(interval-report, NULL,"Get/Set report interval in seconds (format: <30-86400>).",app_config_cmd_config_interval_report, 1, 1),

	SHELL_CMD_ARG(report-interval, NULL, "Set report interval (default: 3600)", app_config_cmd_report_interval, 1, 1),
	SHELL_CMD_ARG(counter-interval-aggreg, NULL, "Set report interval (default: 3600)", app_config_cmd_counter_interval_aggreg, 1, 1),
	SHELL_CMD_ARG(debug-mode, NULL, "Set debug mode (T/F)", app_config_cmd_debug_mode, 1, 1),
	SHELL_CMD_ARG(temperature, NULL, "Set Temperature 0.0f to 50.f", app_config_cmd_temperature, 1, 1),

SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app,

	SHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",
		      print_help, 1, 0),

	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);
SHELL_CMD_REGISTER(sample, NULL, "Sample immediately.", cmd_sample);
SHELL_CMD_REGISTER(send, NULL, "Send data immediately.", cmd_send);
SHELL_CMD_REGISTER(aggreg, NULL, "Aggregate data immediately.", cmd_aggreg);

/* clang-format on */

#include "app_config.h"
#include "app_work.h"


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
SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app_config,

	SHELL_CMD_ARG(show, NULL, "List current configuration." app_config_cmd_config_show, 1, 0),
	SHELL_CMD_ARG(interval-report, NULL,"Get/Set report interval in seconds (format: <30-86400>).",app_config_cmd_config_interval_report, 1, 1),

	SHELL_CMD_ARG(report-interval, NULL, "Set report interval (default: 3600)", app_config_cmd_report_interval, 1, 1),
	SHELL_CMD_ARG(counter-interval-aggreg, NULL, "Set report interval (default: 3600)", app_config_cmd_counter_interval_aggreg, 1, 1),
	SHELL_CMD_ARG(debug-mode, NULL, "Set debug mode (T/F)", app_config_cmd_debug_mode, 1, 1),
	SHELL_CMD_ARG(temperature, NULL, "Set Temperature 0.0f to 50.f", app_config_cmd_temperature, 1, 1),

SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app,

	SHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",
		      print_help, 1, 0),

	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);
SHELL_CMD_REGISTER(sample, NULL, "Sample immediately.", cmd_sample);
SHELL_CMD_REGISTER(send, NULL, "Send data immediately.", cmd_send);
SHELL_CMD_REGISTER(aggreg, NULL, "Aggregate data immediately.", cmd_aggreg);

/* clang-format on */

#include "app_config.h"
#include "app_work.h"


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
SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app_config,

	SHELL_CMD_ARG(show, NULL, "List current configuration." app_config_cmd_config_show, 1, 0),
	SHELL_CMD_ARG(interval-report, NULL,"Get/Set report interval in seconds (format: <30-86400>).",app_config_cmd_config_interval_report, 1, 1),

	SHELL_CMD_ARG(report-interval, NULL, "Set report interval (default: 3600)", app_config_cmd_report_interval, 1, 1),
	SHELL_CMD_ARG(counter-interval-aggreg, NULL, "Set report interval (default: 3600)", app_config_cmd_counter_interval_aggreg, 1, 1),
	SHELL_CMD_ARG(debug-mode, NULL, "Set debug mode (T/F)", app_config_cmd_debug_mode, 1, 1),
	SHELL_CMD_ARG(temperature, NULL, "Set Temperature 0.0f to 50.f", app_config_cmd_temperature, 1, 1),

SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_app,

	SHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",
		      print_help, 1, 0),

	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);
SHELL_CMD_REGISTER(sample, NULL, "Sample immediately.", cmd_sample);
SHELL_CMD_REGISTER(send, NULL, "Send data immediately.", cmd_send);
SHELL_CMD_REGISTER(aggreg, NULL, "Aggregate data immediately.", cmd_aggreg);

/* clang-format on */
