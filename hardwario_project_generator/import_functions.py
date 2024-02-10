'''
CHESTER SDK Project Generator
08/02/2024
Coded by Frese

'''

def create_c_struct(c_file, struct_name, struct_interim_name, data):
    if data == None:
        with open(c_file, 'a') as file:
            file.write('\n')
            file.write('struct' +' '+ struct_name + ' '+ struct_interim_name + ';\n')
    else:
        with open(c_file, 'a') as file:
            file.write('\n')
            file.write('static struct' +' '+ struct_name + ' '+ struct_interim_name + '= {\n')
            for param in data['parameters']:
                if param['type'] == 'int':
                    file.write(f"\t.{param['var']} = {param['default']},\n")
                elif param['type'] == 'bool':
                    default_bool = 'true' if param['default'] else 'false'
                    file.write(f"\t.{param['var']} = {default_bool},\n")
                elif param['type'] == 'float':
                    file.write(f"\t.{param['var']} = {param['default']},\n")
            file.write("};\n")

def create_c_commands(app_config_c, data):
    for command in data['commands']:
        if command['name'] == 'show':
            config_show_beggining = '\n\nint app_config_cmd_config_show(const struct shell *shell, size_t argc, char **argv)\n{\n'
            config = config_show_beggining 
            for parameter in data['parameters']:
                print(parameter)
                if parameter['type'] == 'bool' or parameter['type'] == 'float' or parameter['type'] == 'int':
                    config += f'''\tprint_{parameter['var']}(shell); \n'''
            config_show_end = '\n\treturn 0;\n}'
            config+= config_show_end
            with open(app_config_c, "a") as file:
                file.write(config)
        else: pass
        
def create_h_struct(h_file, struct_name, data):
    if data == None:
         with open(h_file, 'a') as file:
            file.write('\n')
            file.write('extern struct' +' '+ struct_name + ';\n')
    else:
        with open(h_file, 'a') as file:
            file.write('\n')
            file.write('static struct' +' '+ struct_name + ' '+ ' = {\n')
            for param in data['parameters']:
                if param['type'] == 'int':
                    file.write(f"\t{param['type']} {param['var']};\n")
                elif param['type'] == 'bool':
                    default_bool = 'true' if param['default'] else 'false'
                    file.write(f"\t{param['type']} {param['var']};\n")
                elif param['type'] == 'float':
                    file.write(f"\t{param['type']} {param['var']};\n")
            file.write("};\n")

def import_include(keyword, file_path, out_file):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
            for line in lines:
                if keyword in line:
                    with open(out_file, 'a') as arquivo_saida:
                        arquivo_saida.write('\n')
                        arquivo_saida.write(line.strip())
                    return line.strip()

    except FileNotFoundError:
        print(f"File '{file_path}' not found.")
def app_config_h_primitives(file_h, data):
    
    # Parameters
    for parameter in data['parameters']:
        if parameter['type'] == 'bool':
            type = 'bool'
            name_d = parameter['name']
            name_u = parameter['var']
        elif parameter['type'] == 'int':
            type = 'int'
            name_d = parameter['name']
            name_u = parameter['var']
        elif parameter['type'] == 'float':
            type = 'float'
            name_d = parameter['name']
            name_u = parameter['var']
        else: 
            continue

        cmd_config = f'''int app_config_cmd_config_##_name_u(const struct shell *shell, size_t argc, char **argv);'''   
        
        config = '\n\n'
        config += cmd_config.replace("##_name_d", name_d).replace("##_name_u", name_u).replace("#_name_u", name_u).replace("#_name_d", name_d).replace("_name_u", name_u).replace("_name_d", name_d)

      
        with open(file_h, "a") as file:
            file.write(config)
    # Commands
    for command in data['commands']:
        cbk = command['callback']
        config = f'''\n\nint app_config_cmd_config_{cbk}(const struct shell *shell, size_t argc, char **argv);'''   
              
        with open(file_h, "a") as file:
            file.write(config)

def create_app_config_init(file_c, data):
    show_config = '// No config show in this application'

    for command in data['commands']:
        if command['name'] == 'show':
            show_config =  'ctr_config_append_show(SETTINGS_PFX, app_config_cmd_config_show);'
        else:
            continue
    c_code_template = f"""

// Function to handle setting configurations
static int set_setting(const char *key, size_t len, settings_read_cb read_cb, void *cb_arg) {{
    int ret;
    const char *next;
%s
}}

// Function to commit configurations
static int commit_settings(void) {{
    LOG_DBG("Loaded settings in full");
    memcpy(&g_app_config, &m_app_config_interim, sizeof(g_app_config));
    return 0;
}}

// Function to export configurations
static int export_settings(int (*export_func)(const char *name, const void *val, size_t val_len)) {{
    int ret;
%s
}}

// Initialization function
static int init(void) {{
    int ret;

    LOG_INF("System initialization");

    static struct settings_handler sh = {{
        .name = SETTINGS_PFX,
        .h_set = set_setting,
        .h_commit = commit_settings,
        .h_export = export_settings,
    }};

    ret = settings_register(&sh);

    if (ret < 0) {{
        LOG_ERR("Call `settings_register` failed: %d", ret);
        return ret;
    }}

    ret = settings_load_subtree(SETTINGS_PFX);

    if (ret < 0) {{
        LOG_ERR("Call `settings_load_subtree` failed: %d", ret);
        return ret;
    }}

    {show_config}

    return 0;
}}
"""

    set_settings = ''
    export_settings = ''
        
    for parameter in data['parameters']:
        if parameter['type'] == 'bool' or parameter['type'] == 'float' or parameter['type'] == 'int':
            set_settings += f"""
    if (settings_name_steq(key, "{parameter['name']}", &next) && !next) {{
        if (len != sizeof(m_app_config_interim.{parameter['var']})) {{
            return -EINVAL;
        }}
        ret = read_cb(cb_arg, &m_app_config_interim.{parameter['var']}, len);
        if (ret < 0) {{
            LOG_ERR("Call `read_cb` failed: %d", ret);
            return ret;
        }}
        return 0;
    }}
"""

            export_settings += f"""
    ret = export_func("{parameter['name']}", &m_app_config_interim.{parameter['var']}, sizeof(m_app_config_interim.{parameter['var']}));
    if (ret < 0) {{
        return ret;
    }}
"""

    # Print statements for debugging
    print("set_settings:")
    print(set_settings)
    print("export_settings:")
    print(export_settings)

    if set_settings.strip() and export_settings.strip():
        c_code = c_code_template.replace('%s', set_settings).replace('%s', export_settings)
        with open(file_c, "a") as file:
            file.write(c_code)
    else:
        print("No settings to write to the file.")


def cmd_config_function(file_c, parameter):

    if parameter['type'] == 'bool':
        type = 'bool'
        name_d = parameter['name']
        name_u = parameter['var']
    elif parameter['type'] == 'int':
        type = 'int'
        name_d = parameter['name']
        name_u = parameter['var']
        _min = parameter['min']
        _max = parameter['max']
    elif parameter['type'] == 'float':
        type = 'float'
        name_d = parameter['name']
        name_u = parameter['var']
        _min = parameter['min']
        _max = parameter['max']
    else: 
        return
    config = '\n\n'

    cmd_config_bool = f"""static void print_##_name_u(const struct shell *shell)                                     
    {{                                                                                          
        shell_print(shell, "app config #_name_d  %s",m_app_config_interim._name_u ? "true" : "false");                      
    }}     

int app_config_cmd_config_##_name_u(const struct shell *shell, size_t argc, char **argv)   
    {{                                                                                          
        if (argc == 1) {{                                                                   
            print_##_name_u(shell);                                                    
            return 0;                                                                  
        }}                                                                                  
        if (argc == 2) {{                                                                   
            bool is_false = !strcmp(argv[1], "false");                                 
            bool is_true = !strcmp(argv[1], "true");                                   
            if (is_false) {{                                                            
                m_app_config_interim._name_u = false;                              
            }} else if (is_true) {{                                                      
                m_app_config_interim._name_u = true;                               
            }} else {{                                                                   
                shell_error(shell, "invalid format");                              
                return -EINVAL;                                                    
            }}                                                                          
            return 0;                                                                  
        }}                                                                                  
        shell_help(shell);                                                                 
        return -EINVAL;                                                            
    }}"""

    cmd_config_int = f"""static void print_##_name_u(const struct shell *shell)                                     
    {{                                                                                          
        shell_print(shell, "app config  #_name_d  %d", m_app_config_interim._name_u);    
    }}                                                                                          

int app_config_cmd_config_##_name_u(const struct shell *shell, size_t argc, char **argv)   
    {{                                                                                          
        if (argc == 1) {{                                                                   
            print_##_name_u(shell);                                                    
            return 0;                                                                  
        }}                                                                                  
        if (argc == 2) {{                                                                   
            size_t len = strlen(argv[1]);                                              
            for (size_t i = 0; i < len; i++) {{                                         
                if (!isdigit((int)argv[1][i])) {{                                   
                    shell_error(shell, "invalid format");                      
                    return -EINVAL;                                           
                }}                                                                  
            }}                                                                          
            long value = strtol(argv[1], NULL, 10);                                    
            if (value < _min || value > _max) {{                                        
                shell_error(shell, "invalid range");                               
                return -EINVAL;                                                    
            }}                                                                          
            m_app_config_interim._name_u = (int)value;                                 
            return 0;                                                                  
        }}                                                                                  
        shell_help(shell);                                                                 
        return -EINVAL;                                                                  
    }}                                                                 
    """
    cmd_config_float = f"""static void print_##_name_u(const struct shell *shell)                                     
    {{                                                                                          
        shell_print(shell, "app config " #name_d " %.1f", m_app_config_interim._name_u);  
    }}                                                                                          

int app_config_cmd_config_##name_u(const struct shell *shell, size_t argc, char **argv)   
    {{                                                                                          
        if (argc == 1) {{                                                                   
            print_##name_u(shell);                                                    
            return 0;                                                                  
        }}                                                                                  
        if (argc == 2) {{                                                                   
            float value;                                                               
            int ret = sscanf(argv[1], "%f", &value);                                   
            if (ret != 1) {{                                                            
                shell_error(shell, "invalid value");                               
                return -EINVAL;                                                    
            }}                                                                          
            if (value < _min || value > _max) {{                                        
                shell_error(shell, "invalid range");                               
                return -EINVAL;                                                    
            }}                                                                          
            m_app_config_interim._name_u = value;                                      
            return 0;                                                                  
        }}                                                                                  
        shell_help(shell);                                                                 
        return -EINVAL;                                                                    
    }}"""

    if type == 'bool':
        config += cmd_config_bool.replace("##_name_d", name_d).replace("##_name_u", name_u).replace("#_name_u", name_u).replace("#_name_d", name_d).replace("_name_u", name_u).replace("_name_d", name_d)
    elif type == 'int':
        config += cmd_config_int.replace("##_name_d", name_d).replace("##_name_u", name_u).replace("#_name_u", name_u).replace("#_name_d", name_d).replace("_name_u", name_u).replace("_name_d", name_d).replace("_min",str( _min)).replace("_max",str( _max))
    elif type == 'float':
        config += cmd_config_float.replace("##_name_d", name_d).replace("##_name_u", name_u).replace("#_name_u", name_u).replace("#_name_d", name_d).replace("_name_u", name_u).replace("_name_d", name_d).replace("_min",str( _min)).replace("_max",str( _max))
    # Write the function to a C file
    with open(file_c, "a") as file:
        file.write(config)

def write_to_file(list, output_file):

    # Write the function to a C file
    with open(output_file, "a") as file:
        for line in list:
            file.write(line)

if __name__ == '__main__':
    write_to_file()
