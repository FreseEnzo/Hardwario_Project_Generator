#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

# Supported shields: ctr_lte
set(SHIELD ctr_lte)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(CHESTER Clime)

target_sources(app PRIVATE src/app_config.c)
target_sources(app PRIVATE src/app_shell.c)
