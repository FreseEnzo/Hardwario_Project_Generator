import os
import yaml
from jinja2 import Environment, FileSystemLoader
import re

def transform_to_slug(text):
    # Converter para minúsculas
    slug = text.lower()
    # Remover caracteres especiais
    slug = re.sub(r'[^a-zA-Z0-9\s]', '', slug)
    # Substituir espaços por hífens
    slug = slug.replace(' ', '-')
    return slug

def cmake(): 
    
    current_directory = os.getcwd()
    
    # YAML file
    yaml_file = os.path.join(current_directory, "project.yaml")
    with open(yaml_file, 'r') as stream:
        data = yaml.safe_load(stream)
        
    project_name = transform_to_slug(data['project']['name'])
    # Convert YAML data to appropriate format for Jinja
    sources = []
    for root, dirs, files in os.walk(project_name +'/src'):
        sources.append((root, dirs, files))

    env = Environment(loader=FileSystemLoader('..'))
    cmake_path = os.path.join(current_directory,'/scripts/west_commands/hardwario_project_generator/jinja_templates/CMakeLists.j2')
    template = env.get_template(cmake_path)

    # Render the template with data
    project = data['project']
    rendered_template = template.render(project_name=project_name, supported_shields = data['shields'], shields=' '.join(data['shields']), sources=sources)

    # Write the rendered template to CMakeLists.txt
    with open(project_name+'/CMakeLists.txt', "w") as f:
        f.write(rendered_template)
def main():
    cmake()
if __name__ == "__main__":
    main()
    