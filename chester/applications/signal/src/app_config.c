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

#define SETTINGS_PFX "chester-signal"

/* Private Variables -------------------------------------------------------------------*/

struct app_config g_app_config;

static struct app_config m_app_config_interim = {

    .measurement_interval = 60,
    .report_interval = 300,

    /* USER CODE BEGIN Struct Variables */
    /* USER CODE END Struct Variables */
};

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/



static void print_measurement_interval(const struct shell *shell)
{
    shell_print(shell, "app config measurement-interval  %d", m_app_config_interim.measurement_interval);
}

int app_config_cmd_config_measurement_interval(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_measurement_interval(shell);
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
        m_app_config_interim.measurement_interval = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_report_interval(const struct shell *shell)
{
    shell_print(shell, "app config report-interval  %d", m_app_config_interim.report_interval);
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

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
	print_measurement_interval(shell);
	print_report_interval(shell);
    
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

    if (settings_name_steq(key, "measurement-interval", &next) && !next) {
        if (len != sizeof(m_app_config_interim.measurement_interval)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.measurement_interval, len);
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

    ret = export_func("chester-signal/measurement-interval", &m_app_config_interim.measurement_interval,
                      sizeof( m_app_config_interim.measurement_interval));
    if (ret < 0) {
        return ret;
    }

    ret = export_func("chester-signal/report-interval", &m_app_config_interim.report_interval,
                      sizeof( m_app_config_interim.report_interval));
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