'''
CHESTER SDK Project Generator
08/02/2024
Coded by Frese

'''
# Imports 
import yaml # pip install PyYAML
import re
import os
from import_functions import *
from jinja2 import Environment, FileSystemLoader

# File Paths
functions_file = './hardwario_project_generator/params_source/functions.c'
includes_file = './hardwario_project_generator/params_source/includes.c'
app_config_c = './src/app_config.c'
app_config_h = './src/app_config.h'
shell_c = './src/app_shell.c'

# Includes 
config_c_includes = ['"app_config.h"']
app_config_c_includes =['<chester/ctr_config.h>']
app_config_h_includes = []
standard_config_includes = ['<ctype.h>', '<stdbool.h>','<stdio.h>','<stdlib.h>','<string.h>']
zephyr_config_c_includes = ['<zephyr/init.h>','<zephyr/kernel.h>','<zephyr/logging/log.h>','<zephyr/settings/settings.h>','<zephyr/shell/shell.h>']
#Shell
zephyr_includes = ['<zephyr/kernel.h>','<zephyr/logging/log.h>','<zephyr/shell/shell.h>']
shell_includes = ['"app_config.h"','"app_work.h"']
standard_shell_includes = ['<errno.h>','<stdlib.h>']
# Functions
items = [
    '#include <chester/ctr_config.h>',
    '#include <ctype.h>',
    '#include <stdbool.h>',
    '#include <stdlib.h>',
    '#include <string.h>',
    '#include <zephyr/init.h>',
    '#include <zephyr/kernel.h>',
    '#include <zephyr/logging/log.h>',
    '#include <zephyr/settings/settings.h>',
    '#include <zephyr/shell/shell.h>'
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

def transform_to_slug(text):
    # Converter para minúsculas
    slug = text.lower()
    # Remover caracteres especiais
    slug = re.sub(r'[^a-zA-Z0-9\s]', '', slug)
    # Substituir espaços por hífens
    slug = slug.replace(' ', '-')
    return slug

def generate_app_config_c():
    
    try:
        os.mkdir('./src')
    except:
        print('Folder already exists')

    # Setup Jinja environment
    env = Environment(loader=FileSystemLoader('.'))
    template = env.get_template('./hardwario_project_generator/jinja_templates/app_config_c.j2')
    setting_pfx = data['project']

    parameters = data['parameters']
    
    # Render the template with data
    rendered_code = template.render(config_c_includes=config_c_includes,
                                     app_config_c_includes=app_config_c_includes,
                                     zephyr_config_c_includes=zephyr_config_c_includes,
                                     standard_config_includes=standard_config_includes,
                                     struct_data=data,
                                     commands=data['commands'],
                                     setting_pfx = setting_pfx,
                                     parameters = parameters,
                                     data = data,
                                     )
    write_to_file(rendered_code,app_config_c)
 
def generate_app_config_h():

    # Ifndef
    write_to_file('#ifndef APP_CONFIG_H_\n#define APP_CONFIG_H_\n',app_config_h)

    # Includes
    app_config_h_includes.append('\n')
    for include in app_config_h_includes:
        import_include(include,includes_file,app_config_h)

    # Ifndef cpp
    write_to_file('\n#ifdef __cplusplus\nextern "C" {\n#endif\n',app_config_h)

    # Struct
    create_h_struct(app_config_h,'app_config g_app_config',None)
    create_h_struct(app_config_h,'app_config', data)
    # Primitives 
 
    app_config_h_primitives(app_config_h,data)
       
    # Ifndef
    write_to_file('\n\n#ifdef __cplusplus\n}\n#endif\n\n#endif /* APP_CONFIG_H_ */',app_config_h)

def generate_shell():
    # Setup Jinja environment
    env = Environment(loader=FileSystemLoader('.'))
    template = env.get_template('./hardwario_project_generator/jinja_templates/shell_c.j2')

    # Render the template with data
    rendered_code = template.render(shell_includes=shell_includes,zephyr_includes=zephyr_includes, standard_shell_includes=standard_shell_includes,commands=data['commands'], parameters=data['parameters'])

    write_to_file(rendered_code,shell_c)


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
    write_to_file(global_prj_conf,'./prj.conf')

def main():
    
    generate_app_config_c()
    #generate_app_config_h()
    #generate_prj_config_file()
    generate_shell()
   
if __name__ == "__main__":
    main()
    
   
   
    

