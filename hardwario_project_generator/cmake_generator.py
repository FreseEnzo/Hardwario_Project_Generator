'''
CHESTER SDK Project Generator
08/02/2024
Coded by Frese

'''

import os
import yaml # pip install PyYAML

# YAML file
yaml_file = "./params.yaml"
with open(yaml_file, 'r') as stream:
    data = yaml.safe_load(stream)

# Header for the generated CMakeLists.txt
HEADER = """\
#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

# Supported shields: {SHIELDS}
set(SHIELD {SHIELDS})

find_package(Zephyr REQUIRED HINTS $ENV{{ZEPHYR_BASE}})
project({PROJECT_NAME})\n\n"""

# Template for target_sources_ifdef line
TARGET_SOURCES_IFDEF_TEMPLATE = "target_sources_ifdef(CONFIG_{CONFIG} app PRIVATE {SRC})\n"

# Template for target_sources line
TARGET_SOURCES_TEMPLATE = "target_sources(app PRIVATE {SRC})\n"

# Directory to scan for source files
SRC_DIR = "src"

# List of source file extensions to include
SOURCE_EXTENSIONS = [".c"]


def generate_cmake_lists(project_name, shields):
    cmake_content = HEADER.format(PROJECT_NAME=project_name, SHIELDS=' '.join(shields))

    # Iterate over the files in the src directory
    for root, dirs, files in os.walk(SRC_DIR):
        for file in files:
            if any(file.endswith(ext) for ext in SOURCE_EXTENSIONS):
                src_file_path = os.path.join(root, file)
                # Convert the path to use forward slashes
                src_file_path = src_file_path.replace(os.sep, '/')
                cmake_content += TARGET_SOURCES_TEMPLATE.format(SRC=src_file_path)

    # Write the generated CMakeLists.txt content to a file
    with open("CMakeLists.txt", "w") as f:
        f.write(cmake_content)


if __name__ == "__main__":
    project_name = data['project']['name']
    shields = input("Enter the supported shields (separated by space): ").split()

    generate_cmake_lists(project_name, shields)
