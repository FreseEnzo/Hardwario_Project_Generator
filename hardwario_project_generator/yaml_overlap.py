import ruamel.yaml

def compare_yaml(file1, file2, output_file):
    yaml = ruamel.yaml.YAML()
    with open(file1, 'r') as f1:
        yaml1 = yaml.load(f1)

    with open(file2, 'r') as f2:
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
                else:
                    yaml1[key] += value
            elif isinstance(value, dict):
                if key == 'parameters':
                    yaml1[key] = merge_parameters(yaml1[key], value)
                else:
                    yaml1[key].update(value)
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
    merged_params = []
    for param1 in params1:
        found = False
        for param2 in params2:
            if param1['name'] == param2['name']:
                merged_params.append({**param1, **param2})
                found = True
                break
        if not found:
            merged_params.append(param1)
    return merged_params

if __name__ == "__main__":
    file1 = "./params.yaml"
    file2 = "hardwario_project_generator\YAML_Modules\CHESTER_Clime.yaml"
    output_file = "./file3.yaml"
    compare_yaml(file1, file2, output_file)
    print(f"Merged YAML file has been created: {output_file}")
    yaml = ruamel.yaml.YAML()
    with open(output_file, 'r') as f1:
        yaml1 = yaml.load(f1)

