/*
 * Copyright (c) 2023 HARDWARIO a.s.
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

#define SETTINGS_PFX "chester-current"

/* Private Variables -------------------------------------------------------------------*/
struct app_config g_app_config;

static struct app_config m_app_config_interim = {

    .channel_interval_sample = 60,
    .channel_interval_aggreg = 300,
    .interval_report = 900,
    .w1_therm_interval_sample = 60,
    .w1_therm_interval_aggreg = 300,
    .event_report_delay = 1,
    .event_report_rate = 30,
    .backup_report_connected = true,
    .backup_report_disconnected = true,
    .mode = APP_CONFIG_MODE_LTE,

    /* USER CODE BEGIN Struct Variables */
    /* USER CODE END Struct Variables */
};

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
static void print_app_config_mode(const struct shell *shell)
{
	const char *mode;
	switch (m_app_config_interim.mode) {
	case APP_CONFIG_MODE_NONE:
		mode = "none";
		break;
	case APP_CONFIG_MODE_LTE:
		mode = "lte";
		break;
	case APP_CONFIG_MODE_LRW:
		mode = "lrw";
		break;
	default:
		mode = "(unknown)";
		break;
	}

	shell_print(shell, "app config mode %s", mode);
}

int app_config_cmd_config_mode(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_app_config_mode(shell);
		return 0;
	}

	if (argc == 2) {
		if (!strcmp("none", argv[1])) {
			m_app_config_interim.mode = APP_CONFIG_MODE_NONE;
			return 0;
		}

		if (!strcmp("lte", argv[1])) {
			m_app_config_interim.mode = APP_CONFIG_MODE_LTE;
			return 0;
		}

		if (!strcmp("lrw", argv[1])) {
			m_app_config_interim.mode = APP_CONFIG_MODE_LRW;
			return 0;
		}

		shell_error(shell, "invalid option");

		return -EINVAL;
	}

	shell_help(shell);

	return -EINVAL;
}
int app_config_get_interval_report(void)
{
	return m_app_config_interim.interval_report;
}

int app_config_set_interval_report(int value)
{
	if (value < 30 || value > 86400) {
		return -ERANGE;
	}

	m_app_config_interim.interval_report = value;

	return 0;
}

static void print_channel_interval_sample(const struct shell *shell)
{
    shell_print(shell, "app config channel-interval-sample  %d",
            m_app_config_interim.channel_interval_sample);
}

int app_config_cmd_config_channel_interval_sample(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_channel_interval_sample(shell);
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
        m_app_config_interim.channel_interval_sample = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_channel_interval_aggreg(const struct shell *shell)
{
    shell_print(shell, "app config channel-interval-aggreg  %d",
            m_app_config_interim.channel_interval_aggreg);
}

int app_config_cmd_config_channel_interval_aggreg(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_channel_interval_aggreg(shell);
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
        m_app_config_interim.channel_interval_aggreg = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_interval_report(const struct shell *shell)
{
    shell_print(shell, "app config interval-report  %d",
            m_app_config_interim.interval_report);
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

static void print_w1_therm_interval_sample(const struct shell *shell)
{
    shell_print(shell, "app config w1-therm-interval-sample  %d",
            m_app_config_interim.w1_therm_interval_sample);
}

int app_config_cmd_config_w1_therm_interval_sample(const struct shell *shell, size_t argc, char **argv)
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

int app_config_cmd_config_w1_therm_interval_aggreg(const struct shell *shell, size_t argc, char **argv)
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

int app_config_cmd_config_backup_report_connected(const struct shell *shell, size_t argc, char **argv)
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

int app_config_cmd_config_backup_report_disconnected(const struct shell *shell, size_t argc, char **argv)
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

static void print_channel_active(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-active %d %s", i + 1,
			    m_app_config_interim.channel_active[i] ? "true" : "false");
	}
}

int app_config_cmd_config_channel_active(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_active(shell, channel);
		return 0;
	}

	if (argc == 3 && strcmp(argv[2], "true") == 0) {
		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_active[i] = true;
		}

		return 0;
	}

	if (argc == 3 && strcmp(argv[2], "false") == 0) {
		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_active[i] = false;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_channel_differential(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-differential %d %s", i + 1,
			    m_app_config_interim.channel_differential[i] ? "true" : "false");
	}
}

int app_config_cmd_config_channel_differential(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_differential(shell, channel);
		return 0;
	}

	if (argc == 3 && strcmp(argv[2], "true") == 0) {
		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_differential[i] = true;
		}

		return 0;
	}

	if (argc == 3 && strcmp(argv[2], "false") == 0) {
		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_differential[i] = false;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_channel_calib_x0(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-calib-x0 %d %d", i + 1,
			    m_app_config_interim.channel_calib_x0[i]);
	}
}

int app_config_cmd_config_channel_calib_x0(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_calib_x0(shell, channel);
		return 0;
	}

	if (argc == 3) {
		long long val = strtoll(argv[2], NULL, 10);
		if (val < 0 || val > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}

		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_calib_x0[i] = val;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_channel_calib_y0(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-calib-y0 %d %d", i + 1,
			    m_app_config_interim.channel_calib_y0[i]);
	}
}

int app_config_cmd_config_channel_calib_y0(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_calib_y0(shell, channel);
		return 0;
	}

	if (argc == 3) {
		long long val = strtoll(argv[2], NULL, 10);
		if (val < 0 || val > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}

		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_calib_y0[i] = val;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_channel_calib_x1(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-calib-x1 %d %d", i + 1,
			    m_app_config_interim.channel_calib_x1[i]);
	}
}

int app_config_cmd_config_channel_calib_x1(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_calib_x1(shell, channel);
		return 0;
	}

	if (argc == 3) {
		long long val = strtoll(argv[2], NULL, 10);
		if (val < 0 || val > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}

		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_calib_x1[i] = val;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

static void print_channel_calib_y1(const struct shell *shell, int channel)
{
	int ch = channel;

	for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4); i++) {
		shell_print(shell, "app config channel-calib-y1 %d %d", i + 1,
			    m_app_config_interim.channel_calib_y1[i]);
	}
}

int app_config_cmd_config_channel_calib_y1(const struct shell *shell, size_t argc, char **argv)
{
    int channel;

	if (argc >= 2) {
		unsigned long ch = strtoul(argv[1], NULL, 10);

		if (ch < 0 || ch > 4) {
			shell_error(shell, "invalid channel index");
			return -EINVAL;
		}

		channel = ch;
	}

	if (argc == 2) {
		print_channel_calib_y1(shell, channel);
		return 0;
	}

	if (argc == 3) {
		long long val = strtoll(argv[2], NULL, 10);
		if (val < 0 || val > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}

		int ch = channel;

		for (int i = ch != 0 ? ch - 1 : 0; i < (ch != 0 ? ch : 4);
		     i++) {
			m_app_config_interim.channel_calib_y1[i] = val;
		}

		return 0;
	}

	shell_help(shell);
	return -EINVAL;
}

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
    print_app_config_mode(shell);
	print_channel_interval_sample(shell);
	print_channel_interval_aggreg(shell);
	print_interval_report(shell);
	print_w1_therm_interval_sample(shell);
	print_w1_therm_interval_aggreg(shell);
	print_event_report_delay(shell);
	print_event_report_rate(shell);
	print_backup_report_connected(shell);
	print_backup_report_disconnected(shell);
    print_channel_active(shell, 0);
    print_channel_differential(shell, 0);
    print_channel_calib_x0(shell, 0);
    print_channel_calib_y0(shell, 0);
    print_channel_calib_x1(shell, 0);
    print_channel_calib_y1(shell, 0);
    
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
    if (settings_name_steq(key, "mode", &next) && !next) {
        if (len != sizeof(m_app_config_interim.mode)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.mode, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }
    
    if (settings_name_steq(key, "channel-interval-sample", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_interval_sample)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_interval_sample, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }

    if (settings_name_steq(key, "channel-interval-aggreg", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_interval_aggreg)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_interval_aggreg, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }

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

    if (settings_name_steq(key, "channel-active", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_active[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_active[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-active", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_active[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_active[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-active", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_active[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_active[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-active", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_active[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_active[3], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-differential", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_differential[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_differential[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-differential", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_differential[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_differential[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-differential", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_differential[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_differential[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-differential", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_differential[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_differential[3], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x0[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x0[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x0[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x0[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x0[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x0[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x0[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x0[3], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y0[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y0[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y0[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y0[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y0[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y0[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y0", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y0[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y0[3], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x1[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x1[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x1[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x1[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x1[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x1[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-x1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_x1[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_x1[3], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y1[0])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y1[0], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y1[1])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y1[1], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y1[2])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y1[2], len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }    

    if (settings_name_steq(key, "channel-calib-y1", &next) && !next) {
        if (len != sizeof(m_app_config_interim.channel_calib_y1[3])) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.channel_calib_y1[3], len);
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
    ret = export_func("chester-clime/mode", &m_app_config_interim.mode,
                      sizeof( m_app_config_interim.mode));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/channel-interval-sample", &m_app_config_interim.channel_interval_sample,
                      sizeof( m_app_config_interim.channel_interval_sample));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/channel-interval-aggreg", &m_app_config_interim.channel_interval_aggreg,
                      sizeof( m_app_config_interim.channel_interval_aggreg));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/interval-report", &m_app_config_interim.interval_report,
                      sizeof( m_app_config_interim.interval_report));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/w1-therm-interval-sample", &m_app_config_interim.w1_therm_interval_sample,
                      sizeof( m_app_config_interim.w1_therm_interval_sample));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/w1-therm-interval-aggreg", &m_app_config_interim.w1_therm_interval_aggreg,
                      sizeof( m_app_config_interim.w1_therm_interval_aggreg));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/event-report-delay", &m_app_config_interim.event_report_delay,
                      sizeof( m_app_config_interim.event_report_delay));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/event-report-rate", &m_app_config_interim.event_report_rate,
                      sizeof( m_app_config_interim.event_report_rate));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/backup-report-connected", &m_app_config_interim.backup_report_connected,
                      sizeof( m_app_config_interim.backup_report_connected));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/backup-report-disconnected", &m_app_config_interim.backup_report_disconnected,
                      sizeof( m_app_config_interim.backup_report_disconnected));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-current/channel-active", &m_app_config_interim.channel_active[0],
                      sizeof( m_app_config_interim.channel_active[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-active", &m_app_config_interim.channel_active[1],
                      sizeof( m_app_config_interim.channel_active[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-active", &m_app_config_interim.channel_active[2],
                      sizeof( m_app_config_interim.channel_active[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-active", &m_app_config_interim.channel_active[3],
                      sizeof( m_app_config_interim.channel_active[3]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-differential", &m_app_config_interim.channel_differential[0],
                      sizeof( m_app_config_interim.channel_differential[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-differential", &m_app_config_interim.channel_differential[1],
                      sizeof( m_app_config_interim.channel_differential[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-differential", &m_app_config_interim.channel_differential[2],
                      sizeof( m_app_config_interim.channel_differential[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-differential", &m_app_config_interim.channel_differential[3],
                      sizeof( m_app_config_interim.channel_differential[3]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x0", &m_app_config_interim.channel_calib_x0[0],
                      sizeof( m_app_config_interim.channel_calib_x0[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x0", &m_app_config_interim.channel_calib_x0[1],
                      sizeof( m_app_config_interim.channel_calib_x0[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x0", &m_app_config_interim.channel_calib_x0[2],
                      sizeof( m_app_config_interim.channel_calib_x0[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x0", &m_app_config_interim.channel_calib_x0[3],
                      sizeof( m_app_config_interim.channel_calib_x0[3]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y0", &m_app_config_interim.channel_calib_y0[0],
                      sizeof( m_app_config_interim.channel_calib_y0[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y0", &m_app_config_interim.channel_calib_y0[1],
                      sizeof( m_app_config_interim.channel_calib_y0[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y0", &m_app_config_interim.channel_calib_y0[2],
                      sizeof( m_app_config_interim.channel_calib_y0[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y0", &m_app_config_interim.channel_calib_y0[3],
                      sizeof( m_app_config_interim.channel_calib_y0[3]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x1", &m_app_config_interim.channel_calib_x1[0],
                      sizeof( m_app_config_interim.channel_calib_x1[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x1", &m_app_config_interim.channel_calib_x1[1],
                      sizeof( m_app_config_interim.channel_calib_x1[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x1", &m_app_config_interim.channel_calib_x1[2],
                      sizeof( m_app_config_interim.channel_calib_x1[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-x1", &m_app_config_interim.channel_calib_x1[3],
                      sizeof( m_app_config_interim.channel_calib_x1[3]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y1", &m_app_config_interim.channel_calib_y1[0],
                      sizeof( m_app_config_interim.channel_calib_y1[0]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y1", &m_app_config_interim.channel_calib_y1[1],
                      sizeof( m_app_config_interim.channel_calib_y1[1]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y1", &m_app_config_interim.channel_calib_y1[2],
                      sizeof( m_app_config_interim.channel_calib_y1[2]));
    if (ret < 0) {
        return ret;
    }
    
    ret = export_func("chester-current/channel-calib-y1", &m_app_config_interim.channel_calib_y1[3],
                      sizeof( m_app_config_interim.channel_calib_y1[3]));
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