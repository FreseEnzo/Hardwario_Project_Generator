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

#define SETTINGS_PFX "chester-test"

struct app_config g_app_config;

static struct app_config m_app_config_interim = {
	.interval_sample = 60,
	.hygro_t_alarm_hi_thr = 12.45,
	.apn = "onomondo",
	.mode = APP_CONFIG_MODE_LTE,

	/* USER CODE BEGIN Struct Variables */
	/* USER CODE END Struct Variables */
};

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

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

static void print_interval_sample(const struct shell *shell)
{
	shell_print(shell, "app config interval_sample  %d",
			m_app_config_interim.interval_sample);
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
		if (value < 1 || value > 86400) {
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.interval_sample = (int)value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_hygro_t_alarm_hi_thr(const struct shell *shell)
{
	shell_print(shell, "app config hygro-t-alarm-hi-thr %.1f",
			m_app_config_interim.hygro_t_alarm_hi_thr);
}

int app_config_cmd_config_hygro_t_alarm_hi_thr(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_hygro_t_alarm_hi_thr(shell);
		return 0;
	}
	if (argc == 2) {
		float value;
		int ret = sscanf(argv[1], "%f", &value);
		if (ret != 1) {
			shell_error(shell, "invalid value");
			return -EINVAL;
		}
		if (value < -40.0 || value > 125.0) 
		{
			shell_error(shell, "invalid range");
			return -EINVAL;
		}
		m_app_config_interim.hygro_t_alarm_hi_thr = value;
		return 0;
	}
	shell_help(shell);
	return -EINVAL;
}

static void print_apn(const struct shell *shell)
{
	shell_print(shell, "lte config apn %.1f",
			m_app_config_interim.apn);
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

static void print_hygro_t_alarm_lo_report(const struct shell *shell)
{
	shell_print(shell, "app config hygro-t-alarm-lo-report  %s",
			m_app_config_interim.hygro_t_alarm_lo_report ? "true" : "false");
}

int app_config_cmd_config_hygro_t_alarm_lo_report(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		print_hygro_t_alarm_lo_report(shell);                                                    
		return 0;
	}
	if (argc == 2) {
		bool is_false = !strcmp(argv[1], "false");
		bool is_true = !strcmp(argv[1], "true");
		if (is_false) {
			m_app_config_interim.hygro_t_alarm_lo_report = false;
		} else if (is_true) {
			m_app_config_interim.hygro_t_alarm_lo_report = true;
		} else {
			shell_error(shell, "invalid format");
			return -EINVAL;
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
		if (val < 30 || val > 86400) {
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

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
	print_app_config_mode(shell);
	print_interval_sample(shell);
	print_hygro_t_alarm_hi_thr(shell);
	print_apn(shell);
	print_hygro_t_alarm_lo_report(shell);
	print_channel_differential(shell, 0);
	print_channel_calib_x0(shell, 0);
	
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
	
	if (settings_name_steq(key, "interval_sample", &next) && !next) {
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

	if (settings_name_steq(key, "hygro-t-alarm-hi-thr", &next) && !next) {
		if (len != sizeof(m_app_config_interim.hygro_t_alarm_hi_thr)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.hygro_t_alarm_hi_thr, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "apn", &next) && !next) {
		if (len != sizeof(m_app_config_interim.apn)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.apn, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "hygro-t-alarm-lo-report", &next) && !next) {
		if (len != sizeof(m_app_config_interim.hygro_t_alarm_lo_report)) {
			return -EINVAL;
		}
		ret = read_cb(cb_arg, &m_app_config_interim.hygro_t_alarm_lo_report, len);
		if (ret < 0) {
			LOG_ERR("Call `read_cb` failed: %d", ret);
			return ret;
		}
		return 0;
	}

	if (settings_name_steq(key, "channel-0-differential", &next) && !next) {
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

	if (settings_name_steq(key, "channel-1-differential", &next) && !next) {
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

	if (settings_name_steq(key, "channel-2-differential", &next) && !next) {
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

	if (settings_name_steq(key, "channel-3-differential", &next) && !next) {
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

	if (settings_name_steq(key, "channel-0-calib-x0", &next) && !next) {
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

	if (settings_name_steq(key, "channel-1-calib-x0", &next) && !next) {
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

	if (settings_name_steq(key, "channel-2-calib-x0", &next) && !next) {
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

	if (settings_name_steq(key, "channel-3-calib-x0", &next) && !next) {
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

	/* USER CODE BEGIN Functions 2 */
	/* USER CODE END Functions 2 */

	return 0;
}

static int h_export(int (*export_func)(const char *name, const void *val, size_t val_len))
{
	int ret;
	ret = export_func("chester-test/mode", &m_app_config_interim.mode,
					  sizeof( m_app_config_interim.mode));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-test/interval_sample", &m_app_config_interim.interval_sample,
					  sizeof( m_app_config_interim.interval_sample));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-test/hygro-t-alarm-hi-thr", &m_app_config_interim.hygro_t_alarm_hi_thr,
					  sizeof( m_app_config_interim.hygro_t_alarm_hi_thr));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-test/apn", &m_app_config_interim.apn,
					  sizeof( m_app_config_interim.apn));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-test/hygro-t-alarm-lo-report", &m_app_config_interim.hygro_t_alarm_lo_report,
					  sizeof( m_app_config_interim.hygro_t_alarm_lo_report));
	if (ret < 0) {
		return ret;
	}

	ret = export_func("chester-test/channel-0-differential", &m_app_config_interim.channel_differential[0],
					  sizeof( m_app_config_interim.channel_differential[0]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-1-differential", &m_app_config_interim.channel_differential[1],
					  sizeof( m_app_config_interim.channel_differential[1]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-2-differential", &m_app_config_interim.channel_differential[2],
					  sizeof( m_app_config_interim.channel_differential[2]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-3-differential", &m_app_config_interim.channel_differential[3],
					  sizeof( m_app_config_interim.channel_differential[3]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-0-calib-x0", &m_app_config_interim.channel_calib_x0[0],
					  sizeof( m_app_config_interim.channel_calib_x0[0]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-1-calib-x0", &m_app_config_interim.channel_calib_x0[1],
					  sizeof( m_app_config_interim.channel_calib_x0[1]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-2-calib-x0", &m_app_config_interim.channel_calib_x0[2],
					  sizeof( m_app_config_interim.channel_calib_x0[2]));
	if (ret < 0) {
		return ret;
	}
	
	ret = export_func("chester-test/channel-3-calib-x0", &m_app_config_interim.channel_calib_x0[3],
					  sizeof( m_app_config_interim.channel_calib_x0[3]));
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
