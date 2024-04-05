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


def check_vendor(_topdir):
    # Checks if vendor folder exists
    dir_app_vendor = os.path.join(_topdir, "vendor")
    dir_app_chester = os.path.join(_topdir, "chester")
    if "vendor" in os.listdir(_topdir):
        return dir_app_vendor
    else:
        return dir_app_chester


def project_create(_topdir, prj_name):
    # Setup dirs
    dir = check_vendor(_topdir)
    app_dir = os.path.join(dir, "applications")
    prj_dir = generate_project_folder(app_dir, prj_name)
    yaml_dir = os.path.join(prj_dir, "project.yaml")

    # Setup Jinja environment
    jinja_templates_dir = (
        "/scripts/west_commands/hardwario_project_generator/jinja_templates/"
    )
    jinja_templates_folder = os.path.join(
        _topdir,
        "chester",
        *jinja_templates_dir.split("/"),
    )
    env = Environment(loader=FileSystemLoader(jinja_templates_folder))
    template = env.get_template("project_yaml.j2")

    # Render the template with data
    rendered_template = template.render(project_name=prj_name)
    if not os.path.exists(yaml_dir):
        try:
            with open(yaml_dir, "w") as f:
                f.write(rendered_template)
        except:
            log.err("Problem during project.yaml generation")
            sys.exit(1)
    else:
        log.wrn("The project.yaml file already exists in your project folder")
        return False

    return True


def yaml_source(_topdir, prj_name):
    # Setup dirs
    dir = check_vendor(_topdir)
    app_dir = os.path.join(dir, "applications")
    prj_dir = os.path.join(app_dir, prj_name)
    yaml_dir = os.path.join(prj_dir, "project.yaml")

    # YAML file
    try:
        with open(yaml_dir, "r") as stream:
            data = yaml.safe_load(stream)
    except:
        log.wrn(
            "The project.yaml file was not found in the project folder. Please use 'west chester-create <folder_name>' to create the project."
        )
    if not data["project"]["variant"]:
        log.wrn("No project variant found in project.yml.")

    return data


def generate_project_folder(app_dir: str, project_name: str):
    # Create the project directory if it doesn't exist
    project_dir = os.path.join(app_dir, project_name)
    if not os.path.exists(project_dir):
        os.makedirs(project_dir)
    else:
        log.wrn("This project name already exists")
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


def cmake(top_dir, prj_name: str, project_name, data):
    dir = check_vendor(top_dir)
    app_dir = os.path.join(dir, "applications")
    prj_dir = os.path.join(app_dir, prj_name)
    cmake_dir = os.path.join(prj_dir, "CMakeLists.txt")
    src_dir = os.path.join(prj_dir, "src")
    try:
        # Setup Jinja environment
        jinja_templates_dir = (
            "/scripts/west_commands/hardwario_project_generator/jinja_templates"
        )
        jinja_templates_folder = os.path.join(
            top_dir,
            "chester",
            *jinja_templates_dir.split("/"),
        )
        env = Environment(loader=FileSystemLoader(jinja_templates_folder))

        # Walking into files
        sources = []
        for root, dirs, files in os.walk(src_dir):
            # Collect sources
            for file in files:
                if file.endswith(".c"):
                    file_path = os.path.relpath(os.path.join(root, file), src_dir)
                    sources.append(file_path)

        template = env.get_template("CMakeLists.j2")

        # Render the template with data
        rendered_template = template.render(
            project_name=project_name,
            sources=sources,
            data=data,
        )

        # Log message
        if os.path.exists(cmake_dir):
            log.inf("CMakeLists.txt successfully regenerated", colorize=True)
        else:
            log.inf("CMakeLists.txt successfully created", colorize=True)

        # Write the rendered template to CMakeLists.txt
        with open(cmake_dir, "w") as f:
            f.write(rendered_template)
    except:
        log.err("CMakeLists.txt unsuccessfully created")


def generate_file(
    topdir,
    prj_name,
    project_name,
    file_status,
    src_dir,
    out_dir,
    jinja_path,
    **kwargs,
):
    dir = check_vendor(topdir)
    app_dir = os.path.join(dir, "applications")
    prj_dir = os.path.join(app_dir, prj_name)
    try:
        # Setup Jinja environment
        jinja_templates_dir = (
            "/scripts/west_commands/hardwario_project_generator/jinja_templates"
        )
        jinja_templates_folder = os.path.join(
            topdir,
            "chester",
            *jinja_templates_dir.split("/"),
        )
        env = Environment(
            loader=FileSystemLoader(jinja_templates_folder),
            extensions=["jinja2.ext.do"],
        )
        template = env.get_template(jinja_path)

        # Dir source
        src_dir = os.path.join(prj_dir, src_dir)
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
                variant_name=kwargs.get("project", {}).get("variant", ""),
            )

            # Write in destination file
            write_to_file(rendered_code, destination, "w")
            file_status["created"].append(out_dir)
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
                        existing_content[begin_index:end_index]
                    )
                    start_index = end_index

            # Combine saved sections with new content
            for marker in USER_CODE_MARKERS:
                begin_marker = marker["begin"]
                sections = saved_sections.get(begin_marker, [])
                if not sections:
                    continue
                saved_content = "\n".join(section.strip() for section in sections)

                # Concatenate all saved sections
                if saved_content.strip():
                    new_content = new_content.replace(begin_marker, f"{saved_content}")

            # Write in destination file
            write_to_file(new_content, destination, "w")
            file_status["updated"].append(out_dir)
    except:
        log.err(f"{out_dir} unsuccessfully created")


def run(topdir, prj_name, mode):

    file_status: dict[str, list] = {"created": [], "updated": [], "error": []}
    if mode == "create":
        return project_create(topdir, prj_name)

    elif mode == "update":
        data = yaml_source(topdir, prj_name)
        try:
            project_name = transform_to_slug(data["project"]["name"])
        except:
            log.wrn("No project name found in project.yaml. Please update your project.yaml.")
            sys.exit(1)  # Close run

        # Generate app_config.c
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="src",
            out_dir="app_config.c",
            jinja_path="app_config_c.j2",
            **data,
        )

        # Generate app_config.h
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="src",
            out_dir="app_config.h",
            jinja_path="app_config_h.j2",
            **data,
        )

        # Generate app_shell.c
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="src",
            out_dir="app_shell.c",
            jinja_path="app_shell_c.j2",
            **data,
        )

        # Generate prj.confroject.
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="",
            out_dir="prj.conf",
            jinja_path="prj_conf.j2",
            **data,
        )

        # Generate prj.conf
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="",
            out_dir="app.overlay",
            jinja_path="app_overlay.j2",
            **data,
        )

        # Generate Kconfig
        generate_file(
            topdir,
            prj_name,
            project_name,
            file_status,
            src_dir="",
            out_dir="Kconfig",
            jinja_path="k_config.j2",
            **data,
        )

        # Successfull creation log information
        if len(file_status["created"]) > 0:
            log.inf("Created files:", colorize=True)
            for file in file_status["created"]:
                log.inf(f"• {file}", colorize=True)
        if len(file_status["updated"]) > 0:
            log.inf("Updated files:", colorize=True)
            for file in file_status["updated"]:
                log.inf(f"• {file}", colorize=True)

        # Generate CMakeLists.txt
        cmake(topdir, prj_name, project_name, data)
        return True


if __name__ == "__main__":
    run()
