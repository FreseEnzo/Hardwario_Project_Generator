/*
 * Copyright (c) 2024 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */
/* Includes ------------------------------------------------------------------*/
#include "app_config.h"

/* Private includes --------------------------------------------------------------------*/
/* CHESTER includes */
#include <chester/ctr_config.h>

/* Zephyr includes */
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

LOG_MODULE_REGISTER(app_config, LOG_LEVEL_DBG);

#define SETTINGS_PFX "chester-input"

/* Private Variables -------------------------------------------------------------------*/
struct app_config g_app_config;

static struct app_config m_app_config_interim = {
	.interval_report = 1800,
	.event_report_delay = 5,
	.event_report_rate = 30,
	.backup_report_connected = true,
	.backup_report_disconnected = true,
	.trigger_duration_active = 100,
	.trigger_duration_inactive = 100,
	.trigger_cooldown_time = 10,
	.trigger_report_active = true,
	.trigger_report_inactive = true,
	.counter_interval_aggreg = 300,
	.counter_duration_active = 2,
	.counter_duration_inactive = 2,
	.counter_cooldown_time = 10,
	.analog_interval_sample = 60,
	.analog_interval_aggreg = 300,
	.hygro_interval_sample = 60,
	.hygro_interval_aggreg = 300,
	.w1_therm_interval_sample = 60,
	.w1_therm_interval_aggreg = 300,
	.trigger_input_type = APP_CONFIG_INPUT_TYPE_NPN,
	.counter_input_type = APP_CONFIG_INPUT_TYPE_NPN,

	/* USER CODE BEGIN Struct Variables */
	/* USER CODE END Struct Variables */
};

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
static void print_counter_input_type(const struct shell *shell)
{
	const char *type;

	switch (m_app_config_interim.counter_input_type) {
	case APP_CONFIG_INPUT_TYPE_NPN:
		type = "npn";
		break;
	case APP_CONFIG_INPUT_TYPE_PNP:
		type = "pnp";
		break;
	default:
		type = "(unknown)";
		break;
	}

	shell_print(shell, "app config counter-input-type %s", type);
}

int app_config_cmd_config_trigger_input_type(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_trigger_input_type(shell);
		return 0;
	}

	if (argc == 2) {
		bool is_npn = !strcmp(argv[1], "npn");
		bool is_pnp = !strcmp(argv[1], "pnp");

		if (is_npn) {
			m_app_config_interim.trigger_input_type = APP_CONFIG_INPUT_TYPE_NPN;
		} else if (is_pnp) {
			m_app_config_interim.trigger_input_type = APP_CONFIG_INPUT_TYPE_PNP;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_interval_report(const struct shell *shell)
{
	shell_print(shell, "app config interval-report  %d", m_app_config_interim.interval_report);
}

int app_config_cmd_config_interval_report(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_interval_report(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 30 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.interval_report = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_event_report_delay(const struct shell *shell)
{
	shell_print(shell, "app config event-report-delay  %d",
		    m_app_config_interim.event_report_delay);
}

int app_config_cmd_config_event_report_delay(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_event_report_delay(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.event_report_delay = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_event_report_rate(const struct shell *shell)
{
	shell_print(shell, "app config event-report-rate  %d",
		    m_app_config_interim.event_report_rate);
}

int app_config_cmd_config_event_report_rate(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_event_report_rate(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 3600) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.event_report_rate = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_backup_report_connected(const struct shell *shell)
{
	shell_print(shell, "app config backup-report-connected  %s",
		    m_app_config_interim.backup_report_connected ? "true" : "false");
}

int app_config_cmd_config_backup_report_connected(const struct shell *shell, size_t argc,
						  char **argv)
{
	if (argc == 1) {
		print_backup_report_connected(shell);
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.backup_report_connected = false;
		} else if (is_true) {
			m_app_config_interim.backup_report_connected = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_backup_report_disconnected(const struct shell *shell)
{
	shell_print(shell, "app config backup-report-disconnected  %s",
		    m_app_config_interim.backup_report_disconnected ? "true" : "false");
}

int app_config_cmd_config_backup_report_disconnected(const struct shell *shell, size_t argc,
						     char **argv)
{
	if (argc == 1) {
		print_backup_report_disconnected(shell);
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.backup_report_disconnected = false;
		} else if (is_true) {
			m_app_config_interim.backup_report_disconnected = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_trigger_duration_active(const struct shell *shell)
{
	shell_print(shell, "app config trigger-active-duration  %d",
		    m_app_config_interim.trigger_duration_active);
}

int app_config_cmd_config_trigger_duration_active(const struct shell *shell, size_t argc,
						  char **argv)
{
	if (argc == 1) {
		print_trigger_duration_active(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.trigger_duration_active = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_trigger_duration_inactive(const struct shell *shell)
{
	shell_print(shell, "app config trigger-inactive-duration  %d",
		    m_app_config_interim.trigger_duration_inactive);
}

int app_config_cmd_config_trigger_duration_inactive(const struct shell *shell, size_t argc,
						    char **argv)
{
	if (argc == 1) {
		print_trigger_duration_inactive(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.trigger_duration_inactive = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_trigger_cooldown_time(const struct shell *shell)
{
	shell_print(shell, "app config trigger-cooldown-time  %d",
		    m_app_config_interim.trigger_cooldown_time);
}

int app_config_cmd_config_trigger_cooldown_time(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_trigger_cooldown_time(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.trigger_cooldown_time = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_trigger_report_active(const struct shell *shell)
{
	shell_print(shell, "app config trigger-report-active  %s",
		    m_app_config_interim.trigger_report_active ? "true" : "false");
}

int app_config_cmd_config_trigger_report_active(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_trigger_report_active(shell);
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.trigger_report_active = false;
		} else if (is_true) {
			m_app_config_interim.trigger_report_active = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_trigger_report_inactive(const struct shell *shell)
{
	shell_print(shell, "app config trigger-report-inactive  %s",
		    m_app_config_interim.trigger_report_inactive ? "true" : "false");
}

int app_config_cmd_config_trigger_report_inactive(const struct shell *shell, size_t argc,
						  char **argv)
{
	if (argc == 1) {
		print_trigger_report_inactive(shell);
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.trigger_report_inactive = false;
		} else if (is_true) {
			m_app_config_interim.trigger_report_inactive = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_counter_interval_aggreg(const struct shell *shell)
{
	shell_print(shell, "app config counter-interval-aggreg  %d",
		    m_app_config_interim.counter_interval_aggreg);
}

int app_config_cmd_config_counter_interval_aggreg(const struct shell *shell, size_t argc,
						  char **argv)
{
	if (argc == 1) {
		print_counter_interval_aggreg(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.counter_interval_aggreg = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_counter_duration_active(const struct shell *shell)
{
	shell_print(shell, "app config counter-duration-active  %d",
		    m_app_config_interim.counter_duration_active);
}

int app_config_cmd_config_counter_duration_active(const struct shell *shell, size_t argc,
						  char **argv)
{
	if (argc == 1) {
		print_counter_duration_active(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.counter_duration_active = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_counter_duration_inactive(const struct shell *shell)
{
	shell_print(shell, "app config counter-duration-inactive  %d",
		    m_app_config_interim.counter_duration_inactive);
}

int app_config_cmd_config_counter_duration_inactive(const struct shell *shell, size_t argc,
						    char **argv)
{
	if (argc == 1) {
		print_counter_duration_inactive(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.counter_duration_inactive = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_counter_cooldown_time(const struct shell *shell)
{
	shell_print(shell, "app config counter-cooldown-time  %d",
		    m_app_config_interim.counter_cooldown_time);
}

int app_config_cmd_config_counter_cooldown_time(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_counter_cooldown_time(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 0 || value > 60000) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.counter_cooldown_time = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_analog_interval_sample(const struct shell *shell)
{
	shell_print(shell, "app config analog-interval-sample  %d",
		    m_app_config_interim.analog_interval_sample);
}

int app_config_cmd_config_analog_interval_sample(const struct shell *shell, size_t argc,
						 char **argv)
{
	if (argc == 1) {
		print_analog_interval_sample(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.analog_interval_sample = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_analog_interval_aggreg(const struct shell *shell)
{
	shell_print(shell, "app config analog-interval-aggreg  %d",
		    m_app_config_interim.analog_interval_aggreg);
}

int app_config_cmd_config_analog_interval_aggreg(const struct shell *shell, size_t argc,
						 char **argv)
{
	if (argc == 1) {
		print_analog_interval_aggreg(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.analog_interval_aggreg = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_hygro_interval_sample(const struct shell *shell)
{
	shell_print(shell, "app config hygro-interval-sample  %d",
		    m_app_config_interim.hygro_interval_sample);
}

int app_config_cmd_config_hygro_interval_sample(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_hygro_interval_sample(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.hygro_interval_sample = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_hygro_interval_aggreg(const struct shell *shell)
{
	shell_print(shell, "app config hygro-interval-aggreg  %d",
		    m_app_config_interim.hygro_interval_aggreg);
}

int app_config_cmd_config_hygro_interval_aggreg(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_hygro_interval_aggreg(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.hygro_interval_aggreg = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_w1_therm_interval_sample(const struct shell *shell)
{
	shell_print(shell, "app config w1-therm-interval-sample  %d",
		    m_app_config_interim.w1_therm_interval_sample);
}

int app_config_cmd_config_w1_therm_interval_sample(const struct shell *shell, size_t argc,
						   char **argv)
{
	if (argc == 1) {
		print_w1_therm_interval_sample(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.w1_therm_interval_sample = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_w1_therm_interval_aggreg(const struct shell *shell)
{
	shell_print(shell, "app config w1-therm-interval-aggreg  %d",
		    m_app_config_interim.w1_therm_interval_aggreg);
}

int app_config_cmd_config_w1_therm_interval_aggreg(const struct shell *shell, size_t argc,
						   char **argv)
{
	if (argc == 1) {
		print_w1_therm_interval_aggreg(shell);
		return 0;
	}
	if (argc == 2) {
		size_t len = strlen(argv[1]);
		for (size_t i = 0; i < len; i++) {
			if (!isdigit((int)argv[1][i])) {
				shell_error(shell, "invalid format");
				return -EINVAL;
			}
		}
		long value = strtol(argv[1], NULL, 10);
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.w1_therm_interval_aggreg = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
	print_interval_report(shell);
	print_event_report_delay(shell);
	print_event_report_rate(shell);
	print_backup_report_connected(shell);
	print_backup_report_disconnected(shell);
	print_trigger_duration_active(shell);
	print_trigger_duration_inactive(shell);
	print_trigger_cooldown_time(shell);
	print_trigger_report_active(shell);
	print_trigger_report_inactive(shell);
	print_counter_interval_aggreg(shell);
	print_counter_duration_active(shell);
	print_counter_duration_inactive(shell);
	print_counter_cooldown_time(shell);
	print_analog_interval_sample(shell);
	print_analog_interval_aggreg(shell);
	print_hygro_interval_sample(shell);
	print_hygro_interval_aggreg(shell);
	print_w1_therm_interval_sample(shell);
	print_w1_therm_interval_aggreg(shell);

	return 0;
}

/* USER CODE BEGIN Functions 1 */
/* USER CODE END Functions 1 */

static int h_commit(void)
{
	LOG_DBG("Loaded settings in full");
	memcpy(&g_app_config, &m_app_config_interim, sizeof(g_app_config));

	return 0;
}

static int h_set(const char *key, size_t len, settings_read_cb read_cb, void *cb_arg)
{
	int ret;
	const char *next;
	if (settings_name_steq(key, "interval-report", &next) && !next) {
		if (len != sizeof(m_app_config_interim.interval_report)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.interval_report, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "event-report-delay", &next) && !next) {
		if (len != sizeof(m_app_config_interim.event_report_delay)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.event_report_delay, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "event-report-rate", &next) && !next) {
		if (len != sizeof(m_app_config_interim.event_report_rate)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.event_report_rate, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "backup-report-connected", &next) && !next) {
		if (len != sizeof(m_app_config_interim.backup_report_connected)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.backup_report_connected, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "backup-report-disconnected", &next) && !next) {
		if (len != sizeof(m_app_config_interim.backup_report_disconnected)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.backup_report_disconnected, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "trigger-active-duration", &next) && !next) {
		if (len != sizeof(m_app_config_interim.trigger_duration_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.trigger_duration_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "trigger-inactive-duration", &next) && !next) {
		if (len != sizeof(m_app_config_interim.trigger_duration_inactive)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.trigger_duration_inactive, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "trigger-cooldown-time", &next) && !next) {
		if (len != sizeof(m_app_config_interim.trigger_cooldown_time)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.trigger_cooldown_time, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "trigger-report-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.trigger_report_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.trigger_report_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "trigger-report-inactive", &next) && !next) {
		if (len != sizeof(m_app_config_interim.trigger_report_inactive)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.trigger_report_inactive, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "counter-interval-aggreg", &next) && !next) {
		if (len != sizeof(m_app_config_interim.counter_interval_aggreg)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.counter_interval_aggreg, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "counter-duration-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.counter_duration_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.counter_duration_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "counter-duration-inactive", &next) && !next) {
		if (len != sizeof(m_app_config_interim.counter_duration_inactive)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.counter_duration_inactive, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "counter-cooldown-time", &next) && !next) {
		if (len != sizeof(m_app_config_interim.counter_cooldown_time)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.counter_cooldown_time, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "analog-interval-sample", &next) && !next) {
		if (len != sizeof(m_app_config_interim.analog_interval_sample)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.analog_interval_sample, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "analog-interval-aggreg", &next) && !next) {
		if (len != sizeof(m_app_config_interim.analog_interval_aggreg)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.analog_interval_aggreg, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "hygro-interval-sample", &next) && !next) {
		if (len != sizeof(m_app_config_interim.hygro_interval_sample)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.hygro_interval_sample, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "hygro-interval-aggreg", &next) && !next) {
		if (len != sizeof(m_app_config_interim.hygro_interval_aggreg)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.hygro_interval_aggreg, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "w1-therm-interval-sample", &next) && !next) {
		if (len != sizeof(m_app_config_interim.w1_therm_interval_sample)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.w1_therm_interval_sample, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "w1-therm-interval-aggreg", &next) && !next) {
		if (len != sizeof(m_app_config_interim.w1_therm_interval_aggreg)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.w1_therm_interval_aggreg, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	/* USER CODE BEGIN Functions 2 */
	/* USER CODE END Functions 2 */

	return 0;
}

static int h_export(int (*export_func)(const char *name, const void *val, size_t val_len))
{
	int ret;

	ret = export_func("chester-input/interval-report", &m_app_config_interim.interval_report,
			  sizeof(m_app_config_interim.interval_report));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/event-report-delay",
			  &m_app_config_interim.event_report_delay,
			  sizeof(m_app_config_interim.event_report_delay));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/event-report-rate",
			  &m_app_config_interim.event_report_rate,
			  sizeof(m_app_config_interim.event_report_rate));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/backup-report-connected",
			  &m_app_config_interim.backup_report_connected,
			  sizeof(m_app_config_interim.backup_report_connected));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/backup-report-disconnected",
			  &m_app_config_interim.backup_report_disconnected,
			  sizeof(m_app_config_interim.backup_report_disconnected));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/trigger-active-duration",
			  &m_app_config_interim.trigger_duration_active,
			  sizeof(m_app_config_interim.trigger_duration_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/trigger-inactive-duration",
			  &m_app_config_interim.trigger_duration_inactive,
			  sizeof(m_app_config_interim.trigger_duration_inactive));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/trigger-cooldown-time",
			  &m_app_config_interim.trigger_cooldown_time,
			  sizeof(m_app_config_interim.trigger_cooldown_time));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/trigger-report-active",
			  &m_app_config_interim.trigger_report_active,
			  sizeof(m_app_config_interim.trigger_report_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/trigger-report-inactive",
			  &m_app_config_interim.trigger_report_inactive,
			  sizeof(m_app_config_interim.trigger_report_inactive));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/counter-interval-aggreg",
			  &m_app_config_interim.counter_interval_aggreg,
			  sizeof(m_app_config_interim.counter_interval_aggreg));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/counter-duration-active",
			  &m_app_config_interim.counter_duration_active,
			  sizeof(m_app_config_interim.counter_duration_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/counter-duration-inactive",
			  &m_app_config_interim.counter_duration_inactive,
			  sizeof(m_app_config_interim.counter_duration_inactive));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/counter-cooldown-time",
			  &m_app_config_interim.counter_cooldown_time,
			  sizeof(m_app_config_interim.counter_cooldown_time));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/analog-interval-sample",
			  &m_app_config_interim.analog_interval_sample,
			  sizeof(m_app_config_interim.analog_interval_sample));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/analog-interval-aggreg",
			  &m_app_config_interim.analog_interval_aggreg,
			  sizeof(m_app_config_interim.analog_interval_aggreg));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/hygro-interval-sample",
			  &m_app_config_interim.hygro_interval_sample,
			  sizeof(m_app_config_interim.hygro_interval_sample));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/hygro-interval-aggreg",
			  &m_app_config_interim.hygro_interval_aggreg,
			  sizeof(m_app_config_interim.hygro_interval_aggreg));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/w1-therm-interval-sample",
			  &m_app_config_interim.w1_therm_interval_sample,
			  sizeof(m_app_config_interim.w1_therm_interval_sample));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-input/w1-therm-interval-aggreg",
			  &m_app_config_interim.w1_therm_interval_aggreg,
			  sizeof(m_app_config_interim.w1_therm_interval_aggreg));
	if (ret < 0) {
		return ret;
	}

	/* USER CODE BEGIN Functions 3 */
	/* USER CODE END Functions 3 */

	return 0;
}

static int init(void)
{
	int ret;

	LOG_INF("System initialization");

	static struct settings_handler sh = {
		.name = SETTINGS_PFX,
		.h_set = h_set,
		.h_commit = h_commit,
		.h_export = h_export,
	};

	ret = settings_register(&sh);

	if (ret < 0) {
		LOG_ERR("Call `settings_register` failed: %d", ret);
		return ret;
	}

	ret = settings_load_subtree(SETTINGS_PFX);

	if (ret < 0) {
		LOG_ERR("Call `settings_load_subtree` failed: %d", ret);
		return ret;
	}

	ctr_config_append_show(SETTINGS_PFX, app_config_cmd_config_show);

	/* USER CODE BEGIN Functions 4 */
	/* USER CODE END Functions 4 */

	return 0;
}

SYS_INIT(init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);