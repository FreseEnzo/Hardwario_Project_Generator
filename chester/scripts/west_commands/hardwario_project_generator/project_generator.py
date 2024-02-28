"""
CHESTER SDK Project Generator
08/02/2024
Coded by Frese
"""

# Imports
import yaml
import re
import os
from jinja2 import Environment, FileSystemLoader

# Getting current directory
current_directory = os.getcwd()

# Shell features dictionary
dict_features: dict[str, str] = {
    "shell": "CONFIG_ADC_SHELL=y\n",
    "accel": "CONFIG_CTR_ACCEL=y\n",
    "adc": "CONFIG_CTR_ADC=y\n",
    "batt": "CONFIG_CTR_BATT=y\n",
    "bluetooth": "CONFIG_CTR_BLE=y\n",
    "buf": "CONFIG_CTR_BUF=y\n",
    "button": "CONFIG_CTR_BUTTON=y\n",
    "defaults": "CONFIG_CTR_DEFAULTS=y\n",
    "edge": "CONFIG_CTR_EDGE=y\n",
    "info": "CONFIG_CTR_INFO=y\n",
    "led": "CONFIG_CTR_LED=y\n",
    "log": "CONFIG_CTR_LOG=y\n",
    "lte": "CONFIG_CTR_LTE_CLKSYNC=y\n",
    "lorawan": "CONFIG_CTR_LRW=y\n",
    "rtc": "CONFIG_CTR_RTC=y\n",
    "shell": "CONFIG_CTR_SHELL=y\n",
    "therm": "CONFIG_CTR_THERM=y\n",
    "wdog": "CONFIG_CTR_WDOG=y\n",
    "entropy_generator": "CONFIG_ENTROPY_GENERATOR=y\n",
    "tinycrypt_sha256": "CONFIG_TINYCRYPT_SHA256=y\n",
    "tinycrypt": "CONFIG_TINYCRYPT=y\n",
    "zcbor_stop_on_error": "CONFIG_ZCBOR_STOP_ON_ERROR=y\n",
    "zcbor": "CONFIG_ZCBOR=y\n",
}

# User save markers
user_code_markers: list[dict[str, str]] = [
    {"begin": "/* USER CODE BEGIN Includes */", "end": "/* USER CODE END Includes */"},
    {
        "begin": "/* USER CODE BEGIN Variables */",
        "end": "/* USER CODE END Variables */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 0 */",
        "end": "/* USER CODE END Functions 0 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 1 */",
        "end": "/* USER CODE END Functions 1 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 2 */",
        "end": "/* USER CODE END Functions 2 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 3 */",
        "end": "/* USER CODE END Functions 3 */",
    },
    {
        "begin": "/* USER CODE BEGIN Functions 4 */",
        "end": "/* USER CODE END Functions 4 */",
    },
    {"begin": "# USER CODE BEGIN Config", "end": "# USER CODE END Config"},
]

# YAML file
yaml_file = os.path.join(current_directory, "project.yaml")

with open(yaml_file, "r") as stream:
    data = yaml.safe_load(stream)

# Setup Jinja environment base
env = Environment(loader=FileSystemLoader(".."))


def generate_project_folder(project_name):
    # Create the project directory if it doesn't exist
    project_dir = project_name
    if not os.path.exists(project_dir):
        os.makedirs(project_dir)
    return project_dir


def create_project_structure(data):
    # Extract project name from data
    project_name = data.get("project", {}).get("name")
    if not project_name:
        print("Project name not provided in the data.")
        return
    print("Project structure creation completed.")


def write_to_file(list: list, output_file: str, type: str):
    # Write in a file
    with open(output_file, type) as file:
        for line in list:
            file.write(line)


def transform_to_slug(text: str):
    # Convert to lower
    slug = text.lower()
    # Remove special caracters
    slug = re.sub(r"[^a-zA-Z0-9\s]", "", slug)
    # Replace spaces with hyphens
    slug = slug.replace(" ", "-")
    return slug


def cmake(project_name: str):
    # YAML file
    yaml_file = os.path.join(current_directory, "project.yaml")
    with open(yaml_file, "r") as stream:
        data = yaml.safe_load(stream)

    # Convert YAML data to appropriate format for Jinja
    sources = []
    for root, dirs, files in os.walk(project_name + "/src"):
        sources.append((root, dirs, files))

    cmake_path = os.path.join(
        current_directory,
        "/scripts/west_commands/hardwario_project_generator/jinja_templates/CMakeLists.j2",
    )
    template = env.get_template(cmake_path)

    # Render the template with data
    project = data["project"]
    rendered_template = template.render(
        project_name=project_name,
        supported_shields=data["shields"],
        shields=" ".join(data["shields"]),
        sources=sources,
    )

    # Write the rendered template to CMakeLists.txt
    with open(project_name + "/CMakeLists.txt", "w") as f:
        f.write(rendered_template)


def generate_file(**kwargs):
    # Dir source
    src_dir = os.path.join(kwargs["project_dir"], kwargs["src_dir"])
    if not os.path.exists(src_dir):
        os.makedirs(src_dir)
    destination = os.path.join(src_dir, kwargs["out_dir"])

    # Setup Jinja environment
    jinja_path = os.path.join(
        current_directory,
        "/scripts/west_commands/hardwario_project_generator/jinja_templates",
        kwargs["jinja_path"],
    )
    template = env.get_template(jinja_path)

    if not os.path.exists(destination):

        # Render the template with data
        rendered_code = template.render(
            setting_pfx=kwargs["project_name"],
            parameters=data["parameters"],
            commands=data["commands"],
            data=data,
            dict_features=dict_features,
        )

        # Write in destination file
        write_to_file(rendered_code, destination, "w")

    else:
        # Opening destination file
        with open(destination, "r") as file:
            existing_content = file.read()

        # Render the template with data
        new_content = template.render(
            struct_data=data,
            commands=data["commands"],
            setting_pfx=kwargs["project_name"],
            parameters=data["parameters"],
            data=data,
            dict_features=dict_features,
        )

        # Identify and save sections to keep
        saved_sections: dict = {}
        for marker in user_code_markers:
            begin_marker = marker["begin"]
            end_marker = marker["end"]
            saved_sections[begin_marker] = []
            start_index = 0
            while True:
                begin_index = existing_content.find(begin_marker, start_index)
                if begin_index == -1:
                    break
                end_index = existing_content.find(end_marker, begin_index)
                if end_index == -1:
                    break
                saved_sections[begin_marker].append(
                    existing_content[begin_index : end_index - 1]
                )
                start_index = end_index - 1

        # Combine saved sections with new content
        for begin_marker, sections in saved_sections.items():
            saved_content = "\n".join(sections)  # Concatenate all saved sections
            new_content = new_content.replace(begin_marker, f"{saved_content}")

        # Write in destination file
        write_to_file(new_content, destination, "w")


def run():

    project_name = transform_to_slug(data["project"]["name"])
    project_dir = generate_project_folder(project_name)
    create_project_structure(data)

    # Generate app_config.c
    generate_file(
        project_dir=project_dir,
        project_name=project_name,
        src_dir="src",
        out_dir="app_config.c",
        jinja_path="app_config_c.j2",
    )

    # Generate app_config.h
    generate_file(
        project_dir=project_dir,
        project_name=project_name,
        src_dir="src",
        out_dir="app_config.h",
        jinja_path="app_config_h.j2",
    )

    # Generate app_shell.c
    generate_file(
        project_dir=project_dir,
        project_name=project_name,
        src_dir="src",
        out_dir="app_shell.c",
        jinja_path="app_shell_c.j2",
    )

    # Generate prj.conf
    generate_file(
        project_dir=project_dir,
        project_name=project_name,
        src_dir="",
        out_dir="prj.conf",
        jinja_path="prj_conf.j2",
    )

    # Generate CMakeLists.txt
    cmake(project_name)


if __name__ == "__main__":
    run()
