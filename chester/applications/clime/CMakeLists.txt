#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(chester-clime)

target_sources(app PRIVATE src/app_sensor.c)
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/app_shell.c)
target_sources(app PRIVATE src/app_init.c)
target_sources(app PRIVATE src/app_data.c)
target_sources(app PRIVATE src/app_power.c)
target_sources(app PRIVATE src/app_send.c)
target_sources(app PRIVATE src/app_config.c)
target_sources(app PRIVATE src/app_work.c)
target_sources(app PRIVATE src/app_handler.c)
target_sources(app PRIVATE src/app_backup.c)
target_sources(app PRIVATE src/app_cbor.c)    
target_sources_ifdef(CONFIG_APP_TAMPER app PRIVATE src/app_tamper.c)
