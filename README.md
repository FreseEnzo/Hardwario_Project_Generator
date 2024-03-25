# CHESTER SDK Project Generation Tools
## Catalog Progress Review
- [ ] Clime 
- [ ] Signal 
- [ ] Counter 
- [ ] Current 
- [ ] Input
- [ ] Meteo
- [ ] Push
- [ ] Range
- [ ] Scale
      
## Next Steps
- Review

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
### Installation

To use the CHESTER SDK Project Generator, ensure you have the required dependencies installed:

```bash
pip install PyYAML Jinja2
```

### YAML Configuration Example
project.yaml
```yaml
# Hardwario YAML file for code generation
version: 1
project:
  bundle: com.hardwario.chester.clime
  name: CHESTER Clime
  version: v1.0.0
  variant: Clime
features: 
- tamper
- shell
- accel
- batt
- button
- bluetooth
- buf
- defaults
- info
- led
- log
- lte
- lrw
- s2
- rtc
- therm
- wdog
- tinycrypt
- tinycrypt_sha256
- zcbor
- zcbor_stop_on_error
parameters:
- domain: app
  name: interval-sample
  var: interval_sample
  type: int
  min: 1
  max: 86400
  default: 60
  help: 'Get/Set sample interval in seconds (format: <1-86400>).'

- domain: app
  name: interval-aggreg
  var: interval_aggreg
  type: int
  min: 1
  max: 86400
  default: 300
  help: 'Get/Set aggregate interval in seconds (format: <1-86400>).'

- domain: app
  name: interval-report
  var: interval_report
  type: int
  min: 30
  max: 86400
  default: 1800
  help: 'Get/Set report interval in seconds (format: <30-86400>).'

- domain: app
  name: hygro-t-alarm-hi-report
  var: hygro_t_alarm_hi_report
  type: bool
  default: null
  help: 'Get/Set report when hygro high temperature alarm is crossed (format: true, false).'

- domain: app
  name: hygro-t-alarm-lo-report
  var: hygro_t_alarm_lo_report
  type: bool
  default: null
  help: 'Get/Set report when hygro low temperature alarm is crossed (format: true, false).'

- domain: app
  name: hygro-t-alarm-hi-thr
  var: hygro_t_alarm_hi_thr
  type: float
  min: -40.0
  max: 125.0
  default: null
  help: 'Get/Set hygro high temperature alarm threshold (format: <-40.0..125.0>).'

- domain: app
  name: hygro-t-alarm-hi-hst
  var: hygro_t_alarm_hi_hst
  type: float
  min: 0.0
  max: 100.0
  default: null
  help: 'Get/Set hygro high temperature alarm hysteresis (format: <0.0..100.0>).'

- domain: app
  name: hygro-t-alarm-lo-thr
  var: hygro_t_alarm_lo_thr
  type: float
  min: -40.0
  max: 125.0
  default: null
  help: 'Get/Set hygro low temperature alarm threshold (format: <-40.0..125.0>).'

- domain: app
  name: hygro-t-alarm-lo-hst
  var: hygro_t_alarm_lo_hst
  type: float
  min: 0.0
  max: 100.0
  default: null
  help: 'Get/Set hygro low temperature alarm hysteresis (format: <0.0..100.0>).'

- domain: app
  name: event-report-delay
  var: event_report_delay
  type: int
  min: 1
  max: 86400
  default: 1
  help: 'Get/Set event report delay in seconds (format: <1-86400>).'

- domain: app
  name: event-report-rate
  var: event_report_rate
  type: int
  min: 1
  max: 3600
  default: 30
  help: 'Get/Set event report rate in reports per hour (format: <1-3600>).'

- domain: app
  name: backup-report-connected
  var: backup_report_connected
  type: bool
  default: true
  help: 'Set backup report connected (default: true)'

- domain: app
  name: backup-report-disconnected
  var: backup_report_disconnected
  type: bool
  default: true
  help: 'Set backup report disconnected (default: true)'

commands:
- domain: app
  name: sample
  callback: app_work_sample # This function should be manually created
  help: 'Sample immediately.'

- domain: app
  name: send
  callback: app_work_send # This function should be manually created
  help: 'Send data immediately.'

- domain: app
  name: aggreg
  callback: app_work_aggreg # This function should be manually created
  help: 'Aggregate data immediately'

extras:
# Extras for prj.conf
- CONFIG_ADC_TLA2021_INIT_PRIORITY=60 
- CONFIG_ADC_NRFX_SAADC=n
- CONFIG_ADC_SHELL=n
- CONFIG_NEWLIB_LIBC_NANO=n
```
Note: Example generation files can be found in the src directory of this repository

### Usage

1. **Project Configuration**: Ensure you have a 'project.yaml' file that specifies project configurations such as project name, features, commands and extras. Otherwise, just use the command below into your project folder to generate a project.yaml example.
```bash
west scaffold
```
2. **Run the Generator**: This command should be used in project folder with a project.yaml previously configured
```bash
west scaffold
```
