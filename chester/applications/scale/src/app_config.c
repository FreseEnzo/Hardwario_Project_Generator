/*
 * Copyright (c) 2024 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */

#include "app_config.h"

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

#define SETTINGS_PFX "chester-scale"

struct app_config g_app_config;

static struct app_config m_app_config_interim = {
	.channel_a1_active = true,
	.channel_a2_active = true,
	.channel_b1_active = true,
	.channel_b2_active = true,
	.weight_measurement_interval = 60,
	.report_interval = 900,
	.people_measurement_interval = 600,
	.people_counter_power_off_delay = 30,
	.people_counter_stay_timeout = 5,
	.people_counter_adult_border = 4,

	/* USER CODE BEGIN Struct Variables */
	/* USER CODE END Struct Variables */
};

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

static void print_channel_a1_active(const struct shell *shell)
{
	shell_print(shell, "app config channel-a1-active  %s",
			m_app_config_interim.channel_a1_active ? "true" : "false");
}

int app_config_cmd_config_channel_a1_active(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_channel_a1_active(shell);                                                    
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.channel_a1_active = false;
		} else if (is_true) {
			m_app_config_interim.channel_a1_active = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_channel_a2_active(const struct shell *shell)
{
	shell_print(shell, "app config channel-a2-active  %s",
			m_app_config_interim.channel_a2_active ? "true" : "false");
}

int app_config_cmd_config_channel_a2_active(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_channel_a2_active(shell);                                                    
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.channel_a2_active = false;
		} else if (is_true) {
			m_app_config_interim.channel_a2_active = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_channel_b1_active(const struct shell *shell)
{
	shell_print(shell, "app config channel-b1-active  %s",
			m_app_config_interim.channel_b1_active ? "true" : "false");
}

int app_config_cmd_config_channel_b1_active(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_channel_b1_active(shell);                                                    
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.channel_b1_active = false;
		} else if (is_true) {
			m_app_config_interim.channel_b1_active = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_channel_b2_active(const struct shell *shell)
{
	shell_print(shell, "app config channel-b2-active  %s",
			m_app_config_interim.channel_b2_active ? "true" : "false");
}

int app_config_cmd_config_channel_b2_active(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_channel_b2_active(shell);                                                    
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.channel_b2_active = false;
		} else if (is_true) {
			m_app_config_interim.channel_b2_active = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
		}
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_weight_measurement_interval(const struct shell *shell)
{
	shell_print(shell, "app config weight-measurement-interval  %d",
			m_app_config_interim.weight_measurement_interval);
}

int app_config_cmd_config_weight_measurement_interval(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_weight_measurement_interval(shell);
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
		if (value < 5 || value > 3600) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.weight_measurement_interval = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_report_interval(const struct shell *shell)
{
	shell_print(shell, "app config report-interval  %d",
			m_app_config_interim.report_interval);
}

int app_config_cmd_config_report_interval(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_report_interval(shell);
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
		m_app_config_interim.report_interval = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_people_measurement_interval(const struct shell *shell)
{
	shell_print(shell, "app config people-measurement-interval  %d",
			m_app_config_interim.people_measurement_interval);
}

int app_config_cmd_config_people_measurement_interval(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_people_measurement_interval(shell);
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
		if (value < 5 || value > 3600) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.people_measurement_interval = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_people_counter_power_off_delay(const struct shell *shell)
{
	shell_print(shell, "app config people-counter-power-off-delay  %d",
			m_app_config_interim.people_counter_power_off_delay);
}

int app_config_cmd_config_people_counter_power_off_delay(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_people_counter_power_off_delay(shell);
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
		if (value < 0 || value > 255) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.people_counter_power_off_delay = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_people_counter_stay_timeout(const struct shell *shell)
{
	shell_print(shell, "app config people-counter-stay-timeout  %d",
			m_app_config_interim.people_counter_stay_timeout);
}

int app_config_cmd_config_people_counter_stay_timeout(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_people_counter_stay_timeout(shell);
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
		if (value < 0 || value > 255) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.people_counter_stay_timeout = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_people_counter_adult_border(const struct shell *shell)
{
	shell_print(shell, "app config people-counter-adult-border  %d",
			m_app_config_interim.people_counter_adult_border);
}

int app_config_cmd_config_people_counter_adult_border(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_people_counter_adult_border(shell);
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
		if (value < 0 || value > 8) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.people_counter_adult_border = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
	print_channel_a1_active(shell);
	print_channel_a2_active(shell);
	print_channel_b1_active(shell);
	print_channel_b2_active(shell);
	print_weight_measurement_interval(shell);
	print_report_interval(shell);
	print_people_measurement_interval(shell);
	print_people_counter_power_off_delay(shell);
	print_people_counter_stay_timeout(shell);
	print_people_counter_adult_border(shell);
	
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
	if (settings_name_steq(key, "channel-a1-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.channel_a1_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.channel_a1_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "channel-a2-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.channel_a2_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.channel_a2_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "channel-b1-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.channel_b1_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.channel_b1_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "channel-b2-active", &next) && !next) {
		if (len != sizeof(m_app_config_interim.channel_b2_active)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.channel_b2_active, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "weight-measurement-interval", &next) && !next) {
		if (len != sizeof(m_app_config_interim.weight_measurement_interval)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.weight_measurement_interval, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "report-interval", &next) && !next) {
		if (len != sizeof(m_app_config_interim.report_interval)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.report_interval, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "people-measurement-interval", &next) && !next) {
		if (len != sizeof(m_app_config_interim.people_measurement_interval)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.people_measurement_interval, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "people-counter-power-off-delay", &next) && !next) {
		if (len != sizeof(m_app_config_interim.people_counter_power_off_delay)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.people_counter_power_off_delay, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "people-counter-stay-timeout", &next) && !next) {
		if (len != sizeof(m_app_config_interim.people_counter_stay_timeout)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.people_counter_stay_timeout, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "people-counter-adult-border", &next) && !next) {
		if (len != sizeof(m_app_config_interim.people_counter_adult_border)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.people_counter_adult_border, len);
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

	ret = export_func("chester-scale/channel-a1-active", &m_app_config_interim.channel_a1_active,
					  sizeof( m_app_config_interim.channel_a1_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/channel-a2-active", &m_app_config_interim.channel_a2_active,
					  sizeof( m_app_config_interim.channel_a2_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/channel-b1-active", &m_app_config_interim.channel_b1_active,
					  sizeof( m_app_config_interim.channel_b1_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/channel-b2-active", &m_app_config_interim.channel_b2_active,
					  sizeof( m_app_config_interim.channel_b2_active));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/weight-measurement-interval", &m_app_config_interim.weight_measurement_interval,
					  sizeof( m_app_config_interim.weight_measurement_interval));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/report-interval", &m_app_config_interim.report_interval,
					  sizeof( m_app_config_interim.report_interval));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/people-measurement-interval", &m_app_config_interim.people_measurement_interval,
					  sizeof( m_app_config_interim.people_measurement_interval));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/people-counter-power-off-delay", &m_app_config_interim.people_counter_power_off_delay,
					  sizeof( m_app_config_interim.people_counter_power_off_delay));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/people-counter-stay-timeout", &m_app_config_interim.people_counter_stay_timeout,
					  sizeof( m_app_config_interim.people_counter_stay_timeout));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-scale/people-counter-adult-border", &m_app_config_interim.people_counter_adult_border,
					  sizeof( m_app_config_interim.people_counter_adult_border));
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
