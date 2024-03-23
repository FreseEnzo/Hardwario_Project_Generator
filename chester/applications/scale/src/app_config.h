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


/* USER CODE END Includes */

#ifdef __cplusplus
extern "C" {
#endif

/* Private Variables -------------------------------------------------------------------*/
struct app_config {
    bool channel_a1_active;
    bool channel_a2_active;
    bool channel_b1_active;
    bool channel_b2_active;
    int weight_measurement_interval;
    int report_interval;
    int people_measurement_interval;
    int people_counter_power_off_delay;
    int people_counter_stay_timeout;
    int people_counter_adult_border;

    
    /* USER CODE END Struct Variables */
};

extern struct app_config g_app_config;


/* USER CODE END Variables */

/* Private Functions -------------------------------------------------------------------*/
int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_a1_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_a2_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_b1_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_channel_b2_active(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_weight_measurement_interval(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_report_interval(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_people_measurement_interval(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_people_counter_power_off_delay(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_people_counter_stay_timeout(const struct shell *shell, size_t argc, char **argv);
int app_config_cmd_config_people_counter_adult_border(const struct shell *shell, size_t argc, char **argv);


/* USER CODE END Functions 1 */

#ifdef __cplusplus
}
#endif

#endif /* APP_CONFIG_H_ */