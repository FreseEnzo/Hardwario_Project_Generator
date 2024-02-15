#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

# Supported shields: ctr_ds18b20 ctr_lte ctr_x0_a ctr_z 
set(SHIELD ctr_ds18b20 ctr_lte ctr_x0_a ctr_z)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(chester_clime)


target_sources(app PRIVATE ./chester_clime/src/app_config.c)
target_sources(app PRIVATE ./chester_clime/src/app_shell.c)