
/*Copyright (c) 2024 HARDWARIO a.s.*/
/*SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause */
#include "app_config.h"

/* CHESTER includes */
#include <chester/ctr_config.h>

/* Standard includes */
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Zephyr includes */
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>
#include <zephyr/shell/shell.h>

LOG_MODULE_REGISTER(app_config, LOG_LEVEL_DBG);

static struct app_config m_app_config_interimm_app_config_interim = {
	.report_interval = 3600,
	.counter_interval_aggreg = 25,
	.debug_mode = true,
	.temperature = 24.54,
};


static void print_report_interval(const struct shell *shell)                                     
    {                                                                                          
        shell_print(shell, "app config  report-interval  %d", m_app_config_interim.report_interval);    
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
            if (value < 0 || value > 40000) {                                        
                shell_error(shell, "invalid range");                               
                return -EINVAL;                                                    
            }                                                                          
            m_app_config_interim.report_interval = (int)value;                                 
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
    

static void print_debug_mode(const struct shell *shell)                                     
    {                                                                                          
        shell_print(shell, "app config debug-mode  %s",m_app_config_interim.debug_mode ? "true" : "false");                      
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

SYS_INIT(init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);