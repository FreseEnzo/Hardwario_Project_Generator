"""
CHESTER SDK Project Generator
08/02/2024
Coded by Frese
"""

# Imports
import yaml
import re
import os
import sys
from jinja2 import Environment, FileSystemLoader
from project_data import *
from west import log

# Getting current directory
current_directory = os.getcwd()

sucessfully_created = []
sucessfully_updated = []


def folder_verification():

    yaml_file = os.path.join(current_directory, "project.yaml")
    _, folder_name = os.path.split(current_directory)

    if not folder_name == "applications":
        log.wrn("Make sure you're in /applications folder")
        sys.exit(1)  # Close run
    else:
        if not os.path.exists(yaml_file):

            log.wrn(
                "project.yaml file not found. Make sure project.yaml exists in /applications folder."
            )
            sys.exit(1)  # Close run


def yaml_source():
    # YAML file
    yaml_file = os.path.join(current_directory, "project.yaml")

    with open(yaml_file, "r") as stream:
        data = yaml.safe_load(stream)
    return data


def generate_project_folder(project_name: str):
    # Create the project directory if it doesn't exist
    project_dir = project_name
    if not os.path.exists(project_dir):
        os.makedirs(project_dir)
    return project_dir


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


def cmake(project_name: str, data):
    try:
        # Setup Jinja environment
        jinja_templates_dir = (
            "/scripts/west_commands/hardwario_project_generator/jinja_templates"
        )
        current_dir = os.path.dirname(current_directory)
        jinja_templates_folder = os.path.join(
            current_dir,
            *jinja_templates_dir.split("/"),
        )
        env = Environment(loader=FileSystemLoader(jinja_templates_folder))

        # Walking into files
        sources = []
        for root, dirs, files in os.walk(project_name + "/src"):
            sources.append((root, dirs, files))

        template = env.get_template("CMakeLists.j2")

        # Render the template with data
        rendered_template = template.render(
            project_name=project_name,
            sources=sources,
        )

        # Log message
        if os.path.exists(project_name + "/CMakeLists.txt"):
            log.inf("CMakeLists.txt successfully updated", colorize=True)
        else:
            log.inf("CMakeLists.txt successfully created", colorize=True)

        # Write the rendered template to CMakeLists.txt
        with open(project_name + "/CMakeLists.txt", "w") as f:
            f.write(rendered_template)
    except:
        log.err("CMakeLists.txt unsuccessfully created")


def generate_file(project_dir, project_name, src_dir, out_dir, jinja_path, **kwargs):
    try:
        # Setup Jinja environment
        jinja_templates_dir = (
            "/scripts/west_commands/hardwario_project_generator/jinja_templates"
        )
        current_dir = os.path.dirname(current_directory)
        jinja_templates_folder = os.path.join(
            current_dir,
            *jinja_templates_dir.split("/"),
        )
        env = Environment(loader=FileSystemLoader(jinja_templates_folder))
        template = env.get_template(jinja_path)

        # Dir source
        src_dir = os.path.join(project_dir, src_dir)
        if not os.path.exists(src_dir):
            os.makedirs(src_dir)
        destination = os.path.join(src_dir, out_dir)

        if not os.path.exists(destination):

            # Render the template with data
            rendered_code = template.render(
                setting_pfx=project_name,
                parameters=kwargs.get("parameters", ""),
                commands=kwargs.get("commands", ""),
                data=kwargs,
                dict_features=DICT_FEATURES,
                chester_variants=CHESTER_VARIANTS,
                shields_overlay=SHIELDS_OVERLAY,
                variant_name=kwargs.get("project", {}).get("variant", ""),
            )

            # Write in destination file
            write_to_file(rendered_code, destination, "w")
            sucessfully_created.append(out_dir)
        else:
            # Opening destination file
            with open(destination, "r") as file:
                existing_content = file.read()

            # Render the template with data
            new_content = template.render(
                setting_pfx=project_name,
                parameters=kwargs.get("parameters", ""),
                commands=kwargs.get("commands", ""),
                data=kwargs,
                dict_features=DICT_FEATURES,
                chester_variants=CHESTER_VARIANTS,
                shields_overlay=SHIELDS_OVERLAY,
                variant_name=kwargs.get("project", {}).get("variant", ""),
            )

            # Identify and save sections to keep
            saved_sections: dict = {}
            for marker in USER_CODE_MARKERS:
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
            sucessfully_updated.append(out_dir)
    except:
        log.err(f"{out_dir} unsuccessfully created")


def run():

    folder_verification()
    data = yaml_source()
    try:
        project_name = transform_to_slug(data["project"]["name"])
        project_dir = generate_project_folder(project_name)
    except:
        log.wrn("No project name found in project.yaml")
        sys.exit(1)  # Close run

    # Generate app_config.c
    generate_file(
        project_dir,
        project_name,
        src_dir="src",
        out_dir="app_config.c",
        jinja_path="app_config_c.j2",
        **data,
    )

    # Generate app_config.h
    generate_file(
        project_dir,
        project_name,
        src_dir="src",
        out_dir="app_config.h",
        jinja_path="app_config_h.j2",
        **data,
    )

    # Generate app_shell.c
    generate_file(
        project_dir=project_dir,
        project_name=project_name,
        src_dir="src",
        out_dir="app_shell.c",
        jinja_path="app_shell_c.j2",
        **data,
    )

    # Generate prj.confroject.
    generate_file(
        project_dir,
        project_name,
        src_dir="",
        out_dir="prj.conf",
        jinja_path="prj_conf.j2",
        **data,
    )
    # Generate prj.conf
    generate_file(
        project_dir,
        project_name,
        src_dir="",
        out_dir="app.overlay",
        jinja_path="app_overlay.j2",
        **data,
    )

    # Successfull creation log information
    if len(sucessfully_created) > 0:
        log.inf("Created files:", colorize=True)
        for file in sucessfully_created:
            log.inf(f"• {file}", colorize=True)
    if len(sucessfully_updated) > 0:
        log.inf("Updated files:", colorize=True)
        for file in sucessfully_updated:
            log.inf(f"• {file}", colorize=True)
    # Generate CMakeLists.txt
    cmake(project_name, data)

if __name__ == "__main__":
    run()
