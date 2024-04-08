## CHESTER SDK Project Generator
**Author**: [Enzo Frese](https://github.com/FreseEnzo)

**Reviewer** : [José Mendes](https://github.com/jpbaltazar)

This Python project generates a project structure and configuration files for the CHESTER SDK. It provides functionalities to streamline the initialization of projects, including configuration management and shell command setup.

### Features
- **User Code**
  - When the function updates a file, it first reads the existing content of the file.
  - It then iterates through the USER CODE list to identify the sections of user code within the existing content. This is done by searching for the specified marker comments ('begin' and 'end') in the file content.
  - For each identified section of user code, the function stores the content between the corresponding begin and end markers in a dictionary named saved_sections.
  - During the update process, the function replaces the user code sections in the new content with the saved content obtained from the existing file. This ensures that any customizations made by the user are retained in the updated file.

- **YAML Configuration**
  - Utilizes YAML files for project configuration, making it easy to define parameters, features, commands and extras for the project.

- **Structured Configuration Files**
  - Automatically generates files (`app_config.h`, `app_config.c`, `shell.c`, `prj.conf`, `app.overlay`, `Kconfig`) based on the YAML configuration, ensuring consistency and ease of maintenance.

- **Generated CMakeLists.txt**
  - The script generates a CMakeLists.txt file based on the project configuration and source files found in the 'src' directory.
### Usage

1. **Project Create**: 
```bash
west chester-create <name>
```
If there is a `/vendor` folder in your directory, the project will be created in `vendor/application/`, otherwise it will be created in `chester/application/`

2. **Project Update**: 
```bash
west chester-update <name>
```
