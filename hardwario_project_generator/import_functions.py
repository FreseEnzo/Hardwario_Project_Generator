import os
import os.path
import pickle
import re
import sys
import csv
type_list = ['int', 'char', 'float', 'double', 'bool', 'void', 'short', 'long', 'signed', 'struct',]

functions = []

def create_h_struct(filename, struct_name, struct_fields):
    """
    Create a C struct in a .c file.

    Parameters:
    - filename: Name of the .c file
    - struct_name: Name of the struct
    - struct_fields: Dictionary containing field names and types of the struct
                     Example: {'field1': 'int', 'field2': 'float'}

    Returns:
    - None
    """
    with open(filename, 'a') as f:
        f.write('struct ' + struct_name + ' {\n')
        for field, field_type in struct_fields.items():
            f.write('    ' + field_type + ' ' + field + ';\n')
        f.write('};\n\n')

count_struct = 0
def create_c_struct(c_file, struct_name, struct_interim_name, data):

    with open(c_file, 'a') as file:
        file.write('\n')
        file.write('static struct' +' '+ struct_name + ' '+ struct_interim_name + 'm_app_config_interim = {\n')
        for param in data['parameters']:
            if param['type'] == 'int':
                file.write(f"\t.{param['var']} = {param['default']},\n")
            elif param['type'] == 'bool':
                default_bool = 'true' if param['default'] else 'false'
                file.write(f"\t.{param['var']} = {default_bool},\n")
            elif param['type'] == 'float':
                 file.write(f"\t.{param['var']} = {param['default']},\n")
        file.write("};\n")

def create_h_struct(h_file, struct_name, data):

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

def pickle_dump(root_path, data, file_name):
    os.chdir(root_path)
    fp = open(file_name, "w")
    pickle.dump(data, fp)
    fp.close()

def pickle_load(root_path, file_name):
    os.chdir(root_path)
    fp_case = open(file_name, "r")
    dict_case = pickle.load(fp_case)
    fp_case.close()
    return dict_case


def is_valid_name(name):
    if re.match("[a-zA-Z_][a-zA-Z0-9_]*", name) == None:
        return False
    return True

def is_func(line):
#int, __int64, void, char*, char *, struct Node, long long int, (void *)
#int func(int a, int *b, (char *) c)
    line = line.strip()
    if len(line) < 2:
        return None
# Rule 1: assume the function name line must ends with ) or {;
#    if line[-1] != ')' and line[-1] != '{':
#        return None
# Rule 2: (*) must in
    if '(' not in line: #or ')' not in line:
        return None
# Rule 3: # stands for #include or other primitives; / start a comment
    if line[0] == '#' or line[0] == '/':
        return None

# replace pointer * and & as space
    line = re.sub('\*', ' ', line)
    line = re.sub('\&', ' ', line)


# replace '(' as ' ('
    #re.sub('(', ' ( ', line)
    line = re.sub('\(', ' \( ', line)
    line_split = line.split()

    if len(line_split) < 2:
        return None

    bracket_num = 0
    for ch in line:
        if ch == '(':
            bracket_num += 1

    has_type = False
    for type_a in type_list:
        if type_a in line_split[0]:
            has_type = True
#    if has_type == False:
#        return None
#    print line
    if bracket_num == 1:
        for index in range(len(line_split)):
            if '(' in line_split[index]:
                return line_split[index - 1]
    else:
        line = re.sub('\(', ' ', line)
        line = re.sub('\)', ' ', line)
        line_split = line.split()
        index = 0
        for one in line_split:
            if is_valid_name(one):
                index += 1
                if index == 2:
                    return one
        return None

def get_line_type(line):
    line = line.strip()
    if line.startswith("/*"):
#        print line
        return "comment_paragraph"
    elif line.startswith("//"):
        return "comment_line"
    elif line.startswith("#"):
        return "macro"
    return "other"

def is_comment_begin(line):
    if line.startswith("/*"):
        return True
    return False

def is_comment_end(line):
    #print line
    line = line.strip()
    if line.endswith('*/'):
        return True
    return False

def is_func_end(line, left_brack_num):
    line = line.strip()
    left_brack_num += line.count("{")
    if "}" in line:
        left_brack_num -= line.count("}")
        if left_brack_num == 0:
            return True
    return False

def func_name_extract(file_path):

    if not os.path.isfile(file_path):
        print('fdsafafasd')
        return
    

    file_list = []
    with open(file_path, "r") as fp:
        for line in fp.readlines():
            file_list.append(line)

    func_list = []

    i = -1
    while i < len(file_list) - 1:
        i += 1
        line = file_list[i]
        line_type = get_line_type(line)
        if line_type == "comment_line" or line_type == "macro":
            continue
        elif line_type == "comment_paragraph":
            while not is_comment_end(file_list[i]):
                i += 1
        else:
            func_name = is_func(line)
            if func_name != None:
                start_line = i
                left_brack_num = 0
                while True:
                    line = (file_list[i]).strip()
                    left_brack_num += line.count('{')
                    if "}" in line:
                        left_brack_num -= line.count("}")
                        if left_brack_num < 1:
                            break

                    i += 1
                end_line = i
                func_list.append([func_name, start_line + 1, end_line + 1])
    return func_list

def write_to_file(list, output_file):

    # Write the function to a C file
    with open(output_file, "a") as file:
        for line in list:
            file.write(line)

def copy_lines(nome_arquivo_entrada, nome_arquivo_saida, func_name, inicio, fim):
    try:
        with open(nome_arquivo_entrada, 'r') as arquivo_entrada:
            linhas = arquivo_entrada.readlines()

            #check if is a valid interval
            if inicio < 1 or fim > len(linhas) or inicio > fim:
                print("Intervalo de linhas inválido!")
                return

           
            with open(nome_arquivo_saida, 'a') as arquivo_saida:
                arquivo_saida.write('\n\n') 
                for i in range(inicio - 1, fim):
                    arquivo_saida.write(linhas[i])

        print(f"function: {func_name} lines {inicio} to {fim} copied to {nome_arquivo_saida}.")

    except FileNotFoundError:
        print("Arquivo não encontrado!")

def import_function(function_name, source_file, out_file_name):

    func_list = func_name_extract(source_file)
    for function in func_list:
        if function[0] == function_name:
            copy_lines(source_file, out_file_name,function[0], function[1], function[2])
    return func_list
            
if __name__ == '__main__':

    func_list = func_name_extract('functions.c')
    print(func_list)
    match_function = 'print_app_config_mode'
    for function in func_list:
        if function[0] == match_function:
            copy_lines('functions.c', 'out2.c',function[0], function[1], function[2])
    write_to_file(func_list, 'out.c')