#
# Copyright (c) 2024 HARDWARIO a.s.
#
# SPDX-License-Identifier: LicenseRef-HARDWARIO-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

# Supported shields: ctr_lte ctr_s2 
set(SHIELD ctr_lte ctr_s2)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(chester-clime)


target_sources(app PRIVATE src/app_shell.c)
target_sources(app PRIVATE src/app_config.c)