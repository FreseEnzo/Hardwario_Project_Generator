/*
 * Copyright (c) 2023 HARDWARIO a.s.
 *
 * SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
 */
#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* Includes ------------------------------------------------------------------*/

/* Private includes --------------------------------------------------------------------*/

/* Zephyr includes */
#include <zephyr/shell/shell.h>

/* Standard includes */
#include <stdbool.h>
#include <stddef.h>

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

#ifdef __cplusplus
extern "C" {
#endif

/* Private Variables -------------------------------------------------------------------*/
enum app_config_input_type {
	APP_CONFIG_INPUT_TYPE_NPN = 0,
	APP_CONFIG_INPUT_TYPE_PNP = 1,
};

struct app_config {
    enum app_config_input_type trigger_input_type;
    enum app_config_input_type counter_input_type;
    int interval_report;
    int event_report_delay;
    int event_report_rate;
    bool backup_report_connected;
    bool backup_report_disconnected;
    int trigger_duration_active;
    int trigger_duration_inactive;
    int trigger_cooldown_time;
    bool trigger_report_active;
    bool trigger_report_inactive;
    int counter_interval_aggreg;
    int counter_duration_active;
    int counter_duration_inactive;
    int counter_cooldown_time;
    int analog_interval_sample;
    int analog_interval_aggreg;
    int hygro_interval_sample;
    int hygro_interval_aggreg;
    int w1_therm_interval_sample;
    int w1_therm_interval_aggreg;

    /* USER CODE BEGIN Struct Variables */
    /* USER CODE END Struct Variables */
};

extern struct app_config g_app_config;

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_interval_report(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_event_report_delay(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_event_report_rate(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_backup_report_connected(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_backup_report_disconnected(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_duration_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_duration_inactive(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_cooldown_time(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_report_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_report_inactive(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_interval_aggreg(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_duration_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_duration_inactive(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_cooldown_time(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_analog_interval_sample(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_analog_interval_aggreg(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_hygro_interval_sample(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_hygro_interval_aggreg(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_w1_therm_interval_sample(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_w1_therm_interval_aggreg(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_trigger_input_type(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_counter_input_type(const struct shell *shell, size_t argc, char **argv);

/* USER CODE BEGIN Functions 1 */
/* USER CODE END Functions 1 */

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */