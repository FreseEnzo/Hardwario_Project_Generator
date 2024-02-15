/*
 * Copyright (c) 2023 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */
#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* Zephyr includes */
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


struct app_config = {
    
        int report_interval;
        int counter_interval_aggreg;
        char apn [63 + 1];
        bool debug_mode;
        float temperature;
};

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_report_interval(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_interval_aggreg(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_debug_mode(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_temperature(const struct shell *shell, size_t argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */