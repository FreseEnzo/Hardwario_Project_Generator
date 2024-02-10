// APP CONFIG
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

int app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)
{
	print_app_config_mode(shell);

#define CONFIG_PARAM_INT(_name_d, _name_u, _min, _max, _help)	print_##_name_u(shell);


	CONFIG_PARAM_LIST()


	return 0;
}

static int h_set(const char *key, size_t len, settings_read_cb read_cb, void *cb_arg)
{
	int ret;
	const char *next;
}
static int h_commit(void)
{
	LOG_DBG("Loaded settings in full");
	memcpy(&g_app_config, &m_app_config_interim, sizeof(g_app_config));
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
	if (ret) {
		LOG_ERR("Call `settings_register` failed: %d", ret);
		return ret;
	}

	ret = settings_load_subtree(SETTINGS_PFX);
	if (ret) {
		LOG_ERR("Call `settings_load_subtree` failed: %d", ret);
		return ret;
	}

	ctr_config_append_show(SETTINGS_PFX, app_config_cmd_config_show);

	return 0;
}

// APP SHELL
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
static int print_help(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "command not found: %s", argv[1]);
		shell_help(shell);
		return -EINVAL;
	}

	shell_help(shell);

	return 0;
}

