import os
import yaml
from jinja2 import Environment, FileSystemLoader

# YAML file
yaml_file = "./params.yaml"
with open(yaml_file, 'r') as stream:
    data = yaml.safe_load(stream)

# Jinja Template for CMakeLists.txt


# Convert YAML data to appropriate format for Jinja
sources = []
for root, dirs, files in os.walk("src"):
    sources.append((root, dirs, files))

env = Environment(loader=FileSystemLoader('.'))
template = env.get_template('./hardwario_project_generator/jinja_templates/CMakeLists.j2')

# Render the template with data
project = data['project']
rendered_template = template.render(project_name=project['name'], supported_shields = data['shields'], shields=' '.join(data['shields']), sources=sources)



# Write the rendered template to CMakeLists.txt
with open("CMakeLists.txt", "w") as f:
    f.write(rendered_template)

