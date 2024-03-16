# CHESTER SDK Project Generation Tools
## Catalog Progress
- [x] Clime
- [x] Signal
- [ ] Counter
- [ ] Current
- [ ] Input
- [ ] Meteo
- [ ] Push
- [ ] Range
- [ ] Scale
      
## Project Progress
- [x] shell.c
- [x] app_config.c 
- [x] app_config.h
- [x] CMakeList.txt
- [x] prj.conf
- [x] West (west scaffold)
- [x] User code area and automatic code as in STMCubeIDE
- [x] clang-format 
- [x] app.overlay (Verify with Pavel if this solutions is good)
- [x] Warnings (wrong folder or incomplete project file)
- [x] Sinal application working 

## Last Changes
- Improved user code saved
- Signal project.yaml
- Updated warnings
- Moved west command to the project folder
- Added .west 
- Added poetry and dependecies 
- Deleted shield section in CMakeLists.txt
- Added app.overlay generation file
- Added folder and file verification with error message before running the code
- Redone code comments
- Added unique function with kwarg arguments
- Added suggestive names to Jinja templates
- Added cmake function in project_generator.py
- Deleted unused folders and files
- User code area in all files
- Added West scaffold command to generate the skeleton and CMakeLists.txt
- Removed yaml concatenations
- Moved project.yaml /applications

## Next Steps
- Improvements

## CHESTER SDK Project Generator
**Author**: [Enzo Frese](https://github.com/FreseEnzo)

**Reviewer** : [José Mendes](https://github.com/jpbaltazar)

This Python project generates a project structure and configuration files for the CHESTER SDK. It provides functionalities to streamline the initialization of projects, including configuration management and shell command setup.

### Features
- **Preservation of User Code**
  - When the function updates a file, it first reads the existing content of the file.
  - It then iterates through the USER CODE list to identify the sections of user code within the existing content. This is done by searching for the specified marker comments ('begin' and 'end') in the file content.
  - For each identified section of user code, the function stores the content between the corresponding begin and end markers in a dictionary named preserved_sections.
  - During the update process, the function replaces the user code sections in the new content with the preserved content obtained from the existing file. This ensures that any customizations made by the user are retained in the updated file.

- **YAML Configuration**
  - Utilizes YAML files for project configuration, making it easy to define parameters, features, and extras for the project.

- **Structured Configuration Files**
  - Automatically generates C header and source files (`app_config.h` , `app_config.c` , `shell.c`, `prj.conf`) based on the YAML configuration, ensuring consistency and ease of maintenance.
- **Generated CMakeLists.txt**
  - The script generates a CMakeLists.txt file based on the project configuration and source files found in the 'src' directory.
### Installation

To use the CHESTER SDK Project Generator, ensure you have the required dependencies installed:

```bash
pip install PyYAML Jinja2
```

### YAML Configuration Example
project.yaml
```yaml
# Hardwario YAML file for code generation
# Always use Tab for indentation
version: 1
project:
  bundle: com.hardwario.chester.clime
  name: CHESTER Clime
  version: v1.0.3
  variant: Clime 1WH
features:
- bluetooth
- lte
- lorawan
- shell
- led
- button
parameters:
- domain: app
  name: report-interval
  var: report_interval
  type: int
  min: 0
  max: 40000  
  default: 3600
  help: 'Set report interval (default: 3600)'
- domain: app
  name: counter-interval-aggreg
  var: counter_interval_aggreg
  type: int
  min: 32
  max: 324  
  default: 25
  help: 'Set report interval (default: 3600)'
- domain: lte
  name: apn
  var: apn # added 
  type: string
  len: 63 + 1 # added
  default: onomondo
  help: Set APN network name
- domain: app
  name: debug-mode
  var: debug_mode
  type: bool
  default: true
  help: 'Set debug mode (T/F)'
- domain: app
  name: temperature
  var: temperature
  type: float
  default: 24.54
  help: 'Set Temperature 0.0f to 50.f'
commands:
- domain: app
  name: send
  callback: app_send
  help: 'Set report interval (default: 3600)'
- domain: app
  name: show
  callback: show
  help: 'Show all configs'
extras:
- CONFIG_BT=n
- CONFIG_APP_INIT_PRIORITY=50
```
Note: Example generation files can be found in the src directory of this repository


### Usage

1. **Project Configuration**: Ensure you have a 'project.yaml' file that specifies project configurations such as project name, shields, and other settings. Otherwise, just use the command below into your project folder to generate a project.yaml example.
```bash
west scaffold
```
2. **Run the Generator**: This command should be used in project folder with a project.yaml previously configured
```bash
west scaffold
```

### Usage Example

Assuming 'projects.yaml' specifies project configurations, including the project name, you would run the script, provide the supported shields when prompted, and the CMakeLists.txt file will be generated accordingly.

### CMakeLists.txt Example (generated by the YAML above)
```cmake
#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(CHESTER Clime)


target_sources(app PRIVATE src/app_config.c)
target_sources(app PRIVATE src/app_shell.c)
```
