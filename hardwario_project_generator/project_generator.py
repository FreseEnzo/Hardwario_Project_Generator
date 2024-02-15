'''
CHESTER SDK Project Generator
08/02/2024
Coded by Frese

'''
# Imports 
import yaml # pip install PyYAML
import re
import os

from jinja2 import Environment, FileSystemLoader

# File Paths
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


# Shell Parameters
dict_features = {
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
# Setup Jinja environment
env = Environment(loader=FileSystemLoader('.'))

def write_to_file(list, output_file):
    # Write the function to a C file
    with open(output_file, "a") as file:
        for line in list:
            file.write(line)

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
    template = env.get_template('./hardwario_project_generator/jinja_templates/app_config_h.j2')
    rendered_code = template.render(struct_data = data,data = data)
    write_to_file(rendered_code,app_config_h)

def generate_shell():
    template = env.get_template('./hardwario_project_generator/jinja_templates/shell_c.j2')

    # Render the template with data
    rendered_code = template.render(shell_includes=shell_includes,
                                    zephyr_includes=zephyr_includes,
                                    standard_shell_includes=standard_shell_includes,
                                    commands=data['commands'],
                                    parameters=data['parameters'])

    write_to_file(rendered_code,shell_c)


def generate_prj_config_file():

    template = env.get_template('./hardwario_project_generator/jinja_templates/prj_conf.j2')

    # Render the template with data
    rendered_code = template.render(data=data,dict_features = dict_features)

    write_to_file(rendered_code,'./prj.conf')

def main():
    
    generate_app_config_c()
    generate_app_config_h()
    generate_prj_config_file()
    generate_shell()
   
if __name__ == "__main__":
    main()
    
   
   
    

