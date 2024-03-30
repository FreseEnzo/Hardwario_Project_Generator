#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

set(ENV{FW_BUNDLE} "com.hardwario.chester.clime")
set(ENV{FW_VERSION} "v1.0.0")
set(ENV{FW_NAME} "CHESTER Current")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(chester-current)

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
target_sources_ifdef(CONFIG_CTR_BLE app PRIVATE src/app_ble_svc.c)    
target_sources_ifdef(CONFIG_SHIELD_CTR_LTE app PRIVATE src/app_cbor.c)