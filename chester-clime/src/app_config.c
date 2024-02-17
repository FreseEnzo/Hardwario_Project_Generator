/*
 * Copyright (c) 2023 HARDWARIO a.s.
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

LOG_MODULE_REGISTER(app_config, LOG_LEVEL_DBG);

#define SETTINGS_PFX "chester-clime"

struct app_config g_app_config;

static struct app_config g_app_config = {

    .interval_report = 3600,
    .counter_interval_aggreg = 25,
    .apn = "onomondo",
    .debug_mode = true,
    .temperature = 24.54,
    .interval_aggreg = 1800,
    .interval_sample = 25,
    .event_report_delay = 1,
    .event_report_rate = 30,
    .backup_report_connected = true,
    .backup_report_disconnected = true,
    .mode = APP_CONFIG_MODE_LTE,

};


static void print_interval_report(const struct shell *shell)
{
    shell_print(shell, "app config  interval-report  %d", m_app_config_interim.interval_report);
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
        if (value < 0 || value > 40000) {
            shell_error(shell, "invalid range");
            return -EINVAL;
        }
        m_app_config_interim.interval_report = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_counter_interval_aggreg(const struct shell *shell)
{
    shell_print(shell, "app config  counter-interval-aggreg  %d", m_app_config_interim.counter_interval_aggreg);
}

int app_config_cmd_config_counter_interval_aggreg(const struct shell *shell, size_t argc, char **argv)
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
        if (value < 32 || value > 324) {
            shell_error(shell, "invalid range");
            return -EINVAL;
        }
        m_app_config_interim.counter_interval_aggreg = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_apn(const struct shell *shell)
{
    shell_print(shell, "app config apn %.1f", m_app_config_interim.apn);
}

int app_config_cmd_config_apn(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_apn(shell);
        return 0;
    }
    if (argc == 2) {
            size_t len = strlen(argv[1]);

            if (len >= sizeof(m_config_interim.apn)) {
                shell_error(shell, "invalid format");
                return -EINVAL;
            }

            for (size_t i = 0; i < len; i++) {
                char c = argv[1][i];
                if (!isalnum((int)c) && c != '-' && c != '.') {
                    shell_error(shell, "invalid format");
                    return -EINVAL;
                }
            }

            strcpy(m_config_interim.apn, argv[1]);
            return 0;
        }
    shell_help(shell);
    return -EINVAL;
}

static void print_debug_mode(const struct shell *shell)
{
    shell_print(shell, "app config debug-mode  %s", m_app_config_interim.debug_mode ? "true" : "false");
}

int app_config_cmd_config_debug_mode(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_debug_mode(shell);                                                    
        return 0;
    }
    if (argc == 2) {
        bool is_false = !strcmp(argv[1], "false");
        bool is_true = !strcmp(argv[1], "true");
        if (is_false) {
            m_app_config_interim.debug_mode = false;
        } else if (is_true) {
            m_app_config_interim.debug_mode = true;
        } else {
            shell_error(shell, "invalid format");
            return -EINVAL;
        }
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_temperature(const struct shell *shell)
{
    shell_print(shell, "app config temperature %.1f", m_app_config_interim.temperature);
}

int app_config_cmd_config_temperature(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_temperature(shell);
        return 0;
    }
    if (argc == 2) {
        float value;
        int ret = sscanf(argv[1], "%f", &value);
        if (ret != 1) {
            shell_error(shell, "invalid value");
            return -EINVAL;
        }
        if (value <  || value > ) {
            shell_error(shell, "invalid range");
            return -EINVAL;
        }
        m_app_config_interim.temperature = value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_interval_aggreg(const struct shell *shell)
{
    shell_print(shell, "app config  interval-aggreg  %d", m_app_config_interim.interval_aggreg);
}

int app_config_cmd_config_interval_aggreg(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_interval_aggreg(shell);
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
        if (value < 0 || value > 65535) {
            shell_error(shell, "invalid range");
            return -EINVAL;
        }
        m_app_config_interim.interval_aggreg = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_interval_sample(const struct shell *shell)
{
    shell_print(shell, "app config  interval-sample  %d", m_app_config_interim.interval_sample);
}

int app_config_cmd_config_interval_sample(const struct shell *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_interval_sample(shell);
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
        if (value < 0 || value > 65535) {
            shell_error(shell, "invalid range");
            return -EINVAL;
        }
        m_app_config_interim.interval_sample = (int)value;
        return 0;
    }
    shell_help(shell);
    return -EINVAL;
}

static void print_event_report_delay(const struct shell *shell)
{
    shell_print(shell, "app config  event-report-delay  %d", m_app_config_interim.event_report_delay);
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
        if (value < 0 || value > 65535) {
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
    shell_print(shell, "app config  event-report-rate  %d", m_app_config_interim.event_report_rate);
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
        if (value < 0 || value > 65535) {
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
    shell_print(shell, "app config backup-report-connected  %s", m_app_config_interim.backup_report_connected ? "true" : "false");
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
    shell_print(shell, "app config backup-report-disconnected  %s", m_app_config_interim.backup_report_disconnected ? "true" : "false");
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

// Function to handle setting configurations
static int set_setting(const char *key, size_t len, settings_read_cb read_cb, void *cb_arg) {
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


if (settings_name_steq(key, "debug-mode", &next) && !next) {
            if (len != sizeof(m_app_config_interim.debug_mode)) {
                return -EINVAL;
            }
            ret = read_cb(cb_arg, &m_app_config_interim.debug_mode, len);
            if (ret < 0) {
                LOG_ERR("Call `read_cb` failed: %d", ret);
                return ret;
            }
            return 0;
        }

if (settings_name_steq(key, "temperature", &next) && !next) {
            if (len != sizeof(m_app_config_interim.temperature)) {
                return -EINVAL;
            }
            ret = read_cb(cb_arg, &m_app_config_interim.temperature, len);
            if (ret < 0) {
                LOG_ERR("Call `read_cb` failed: %d", ret);
                return ret;
            }
            return 0;
        }

if (settings_name_steq(key, "interval-aggreg", &next) && !next) {
            if (len != sizeof(m_app_config_interim.interval_aggreg)) {
                return -EINVAL;
            }
            ret = read_cb(cb_arg, &m_app_config_interim.interval_aggreg, len);
            if (ret < 0) {
                LOG_ERR("Call `read_cb` failed: %d", ret);
                return ret;
            }
            return 0;
        }

if (settings_name_steq(key, "interval-sample", &next) && !next) {
            if (len != sizeof(m_app_config_interim.interval_sample)) {
                return -EINVAL;
            }
            ret = read_cb(cb_arg, &m_app_config_interim.interval_sample, len);
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


}
// Function to export configurations
static int export_settings(int (*export_func)(const char *name, const void *val, size_t val_len)) {
    int ret;
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

    if (settings_name_steq(key, "debug-mode", &next) && !next) {
        if (len != sizeof(m_app_config_interim.debug_mode)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.debug_mode, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }

    if (settings_name_steq(key, "temperature", &next) && !next) {
        if (len != sizeof(m_app_config_interim.temperature)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.temperature, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }

    if (settings_name_steq(key, "interval-aggreg", &next) && !next) {
        if (len != sizeof(m_app_config_interim.interval_aggreg)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.interval_aggreg, len);
        if (ret < 0) {
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }
        return 0;
    }

    if (settings_name_steq(key, "interval-sample", &next) && !next) {
        if (len != sizeof(m_app_config_interim.interval_sample)) {
            return -EINVAL;
        }
        ret = read_cb(cb_arg, &m_app_config_interim.interval_sample, len);
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
}

// Initialization function
static int init(void) {
    int ret;

    LOG_INF("System initialization");

    static struct settings_handler sh = {
        .name = SETTINGS_PFX,
        .h_set = set_setting,
        .h_commit = commit_settings,
        .h_export = export_settings,
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
    ctr_config_append_show(SETTINGS_PFX, app_config_cmd_config_show)
    

    return 0;
}

SYS_INIT(init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

