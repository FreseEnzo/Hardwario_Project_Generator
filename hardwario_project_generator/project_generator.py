'''
CHESTER SDK Project Generator
08/02/2024
Coded by Frese

'''
# Imports 
import yaml # pip install PyYAML
import re
from import_functions import *

# File Paths
functions_file = './hardwario_project_generator/params_source/functions.c'
includes_file = './hardwario_project_generator/params_source/includes.c'
app_config_c = './src/app_config.c'
app_config_h = './src/app_config.h'
shell_c = './src/app_shell.c'

# --- Includes ---
app_config_c_includes = ['Copyrigh','License','app_config']
app_config_h_includes = ['Zephyr','shell','Standard','stddef']
chester_includes = ['CHESTER','ctr_config']
standard_includes = ['Standard','ctype', 'stdbool','stdio','stdlib','string']
zephyr_includes = ['Zephyr','init','kernel','log','settings','shell']
shell_includes = ['app_config','app_work']

# Functions
app_config_functions = ['print_app_config_mode','app_config_cmd_config_mode','h_set','h_commit','init']
shell_functions = ['cmd_sample','cmd_send','cmd_aggreg']
shell_standard_functions = [
    'SHELL_STATIC_SUBCMD_SET_CREATE(\n',
    '\tsub_app,\n',
    '\n',
    '\tSHELL_CMD_ARG(config, &sub_app_config, "Configuration commands.",\n',
    '\t\t      print_help, 1, 0),\n',
    '\n',
    '\tSHELL_SUBCMD_SET_END\n',
    ');\n',
    '\n',
    'SHELL_CMD_REGISTER(app, &sub_app, "Application commands.", print_help);\n',
    'SHELL_CMD_REGISTER(sample, NULL, "Sample immediately.", cmd_sample);\n',
    'SHELL_CMD_REGISTER(send, NULL, "Send data immediately.", cmd_send);\n',
    'SHELL_CMD_REGISTER(aggreg, NULL, "Aggregate data immediately.", cmd_aggreg);\n',
    '\n',
    '/* clang-format on */\n'
]

# Shell Parameters
basic_parameters = ['# Basic Parameters\n','CONFIG_ARM=y\n','CONFIG_BOARD_CHESTER_NRF52840=y\n']
config_parameters = {
    'shell': 'CONFIG_ADC_SHELL=y\n',
    'accel': 'CONFIG_CTR_ACCEL=y\n',
    'adc': 'CONFIG_CTR_ADC=y\n',
    'batt': 'CONFIG_CTR_BATT=y\n',
    'bluetooth': 'CONFIG_CTR_BLE=y\n',
    'buf': 'CONFIG_CTR_BUF=y\n',
    'button': 'CONFIG_CTR_BUTTON=y\n',
    'defaults': 'CONFIG_CTR_DEFAULTS=y\n',
    'edge': 'CONFIG_CTR_EDGE=y\n',
    'info': 'CONFIG_CTR_INFO=y\n',
    'led': 'CONFIG_CTR_LED=y\n',
    'log': 'CONFIG_CTR_LOG=y\n',
    'lte': 'CONFIG_CTR_LTE_CLKSYNC=y\n',
    'lorawan': 'CONFIG_CTR_LRW=y\n',
    'rtc': 'CONFIG_CTR_RTC=y\n',
    'shell': 'CONFIG_CTR_SHELL=y\n',
    'therm': 'CONFIG_CTR_THERM=y\n',
    'wdog': 'CONFIG_CTR_WDOG=y\n',
    'entropy_generator': 'CONFIG_ENTROPY_GENERATOR=y\n',
    'tinycrypt_sha256': 'CONFIG_TINYCRYPT_SHA256=y\n',
    'tinycrypt': 'CONFIG_TINYCRYPT=y\n',
    'zcbor_stop_on_error': 'CONFIG_ZCBOR_STOP_ON_ERROR=y\n',
    'zcbor': 'CONFIG_ZCBOR=y\n'
}

# YAML file
yaml_file = "./params.yaml"
with open(yaml_file, 'r') as stream:
    data = yaml.safe_load(stream)

def generate_app_config_c():
    try:
        os.mkdir('./src')
    except:
        print('folder already exists')

    # Includes import
    app_config_c_includes.append('\n')
    chester_includes.append('\n')
    standard_includes.append('\n')
    shell_includes.append('\n')

    app_config_includes =  app_config_c_includes + chester_includes + standard_includes + zephyr_includes 
    for include in app_config_includes:
        import_include(include,includes_file,app_config_c)

    # LOG
    write_to_file('\n\nLOG_MODULE_REGISTER(app_config, LOG_LEVEL_DBG);\n',app_config_c)

    # Creating Struct
    create_c_struct(app_config_c,'app_config','m_app_config_interim', data)

    #Functions Creations
    for parameter in data['parameters']:
        try:
            cmd_config_function(app_config_c,parameter)
        except:
            pass

    # Functions import 
    for function in app_config_functions:
        func_list = import_function(function,functions_file,app_config_c)
        print(func_list)
    write_to_file('\nSYS_INIT(init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);',app_config_c)
 
def generate_app_config_h():

    write_to_file('#ifndef APP_CONFIG_H_\n#define APP_CONFIG_H_\n',app_config_h)
    app_config_h_includes.append('\n')
    for include in app_config_h_includes:
        import_include(include,includes_file,app_config_h)
    write_to_file('\n#ifdef __cplusplus\nextern "C" {\n#endif',app_config_h)
    create_h_struct(app_config_h,'app_config', data)
    write_to_file('\n#ifdef __cplusplus\n}\n#endif  /* APP_CONFIG_H_ */',app_config_h)

def generate_shell():
    # Includes
    shell_includes.append('\n')
    zephyr_includes.append('\n')
    standard_includes.append('\n')
    app_shell_includes = shell_includes + zephyr_includes + standard_includes
    for include in app_shell_includes: 
        import_include(include,includes_file,shell_c)
    #LOG
    write_to_file('\nLOG_MODULE_REGISTER(app_shell, LOG_LEVEL_INF);\n',shell_c)
    # Functions
    for function in shell_functions:
        func_list = import_function(function,functions_file,shell_c)
    print(func_list)

    # Shell CMD
    shell_cmds = [
                'SHELL_STATIC_SUBCMD_SET_CREATE(\n',
                '\tsub_app_config,\n',
                '\n',
                '\tSHELL_CMD_ARG(show, NULL, "List current configuration." app_config_cmd_config_show, 1, 0),\n',
                '\tSHELL_CMD_ARG(interval-report, NULL,"Get/Set report interval in seconds (format: <30-86400>).",app_config_cmd_config_interval_report, 1, 1),\n\n'
                ]
    for parameter in data['parameters']:
        try:
            shell_cmds += f"\tSHELL_CMD_ARG({parameter['name']}, NULL, \"{parameter['help']}\", app_config_cmd_{parameter['var']}, 1, 1),\n"
        except:
            pass
    shell_cmds += '\nSHELL_SUBCMD_SET_END\n);\n\n'
    write_to_file(shell_cmds,shell_c)
    write_to_file(shell_standard_functions,shell_c)
        

def generate_cmake_file():
    # Generate the CMakeLists.txt file based on instructions
    # You can implement your logic here
    pass

def generate_prj_config_file():
    # Basic Parameters
    global_prj_conf = basic_parameters
    
    # Feature Parameters
    global_prj_conf.append('\n#Parameters specified by features\n')
    for feature in data['features']:
        if feature in config_parameters:
            global_prj_conf.append(config_parameters[feature])

    #Extra Parameters
    global_prj_conf.append('\n# Extra parameters\n')
    new_extras = [line + '\n' for line in data['extras']]
    global_prj_conf += new_extras
    print(global_prj_conf)
    write_to_file(global_prj_conf,'./prj.conf')

def main():
    
    generate_app_config_c()
    generate_app_config_h()
    generate_prj_config_file()
    generate_shell()
   
if __name__ == "__main__":
    main()
    
   
   
    

