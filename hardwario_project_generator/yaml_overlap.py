import ruamel.yaml
import os
import yaml

def encontrar_yaml(nome_projeto, pasta):
    # Caminho completo para o arquivo YAML com base no nome do projeto
    nome_arquivo_yaml = nome_projeto.replace(" ", "_") + ".yaml"
    caminho_completo = os.path.join(pasta, nome_arquivo_yaml)

    # Verifica se o arquivo YAML existe na pasta especificada
    if os.path.exists(caminho_completo):
        return caminho_completo
    else:
        # Se o arquivo não existir, retorna None
        return None

# Exemplo de uso da f
def compare_yaml(file1, variant, output_file):


    yaml = ruamel.yaml.YAML()

    with open(file1, 'r') as f1:
        yaml1 = yaml.load(f1)
    

    with open(encontrar_yaml(variant,'hardwario_project_generator/YAML_Modules'), 'r') as f2:
        yaml2 = yaml.load(f2)

    # Merge yaml2 into yaml1
    for key, value in yaml2.items():
        if key in yaml1:
            if isinstance(value, list):
                if key == 'features':
                    merge_features(yaml1, value)
                elif key == 'shields':
                    merge_shields(yaml1, value)
                elif key == 'commands':
                    merge_commands(yaml1, value)
                elif key == 'extras':
                    merge_extras(yaml1, value)
                elif key == 'parameters':
                    yaml1[key] = merge_parameters(yaml1[key], value)
                else:
                    yaml1[key] += value

        else:
            yaml1[key] = value

    # Write the merged YAML to the output file
    with open(output_file, 'w') as outfile:
        yaml.dump(yaml1, outfile)

def merge_features(yaml1, features2):
    features1_set = set(yaml1['features'])
    for feature in features2:
        if feature not in features1_set:
            yaml1['features'].append(feature)

def merge_shields(yaml1, shields2):
    shields1_set = set(yaml1['shields'])
    for shield in shields2:
        if shield not in shields1_set:
            yaml1['shields'].append(shield)

def merge_commands(yaml1, commands2):
    commands1_set = set((cmd['name'], cmd['domain']) for cmd in yaml1['commands'])
    for cmd in commands2:
        if (cmd['name'], cmd['domain']) not in commands1_set:
            yaml1['commands'].append(cmd)

def merge_extras(yaml1, extras2):
    extras1_set = set(yaml1['extras'])
    for extra in extras2:
        if extra not in extras1_set:
            yaml1['extras'].append(extra)

def merge_parameters(params1, params2):
    param_dict = {param['name']: param for param in params1}
    for param in params2:
        if param['name'] not in param_dict:
            params1.append(param)
      
        else:
            existing_param = param_dict[param['name']]
            for key, value in param.items():
                if key not in existing_param:
                    existing_param[key] = value
    return params1

def generate_project_yaml():
    file1 = "./params.yaml"
    output_file = "./project.yaml"

    with open(file1, 'r') as stream:
        data = yaml.safe_load(stream)

    compare_yaml(file1, data['project']['variant'], output_file)
    print(f"Project YAML file has been created: {output_file}")


