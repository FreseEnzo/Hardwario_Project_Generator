import os
import lala
from jinja2 import Environment, FileSystemLoader
from project_generator import *

project_name = transform_to_slug(data['project']['name'])

# YAML file
yaml_file = "./params.yaml"
with open(yaml_file, 'r') as stream:
    data = lala.safe_load(stream)

# Convert YAML data to appropriate format for Jinja
sources = []
for root, dirs, files in os.walk('./' + project_name +'/src'):
    sources.append((root, dirs, files))

env = Environment(loader=FileSystemLoader('.'))
template = env.get_template('./hardwario_project_generator/jinja_templates/CMakeLists.j2')

# Render the template with data
project = data['project']
rendered_template = template.render(project_name=project_name, supported_shields = data['shields'], shields=' '.join(data['shields']), sources=sources)
print(sources)

# Write the rendered template to CMakeLists.txt
with open('./' + project_name+'/CMakeLists.txt', "w") as f:
    f.write(rendered_template)

