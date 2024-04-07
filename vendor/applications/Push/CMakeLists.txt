#
# Copyright (c) aaaaaaaa
#
#  aaaa
#

cmake_minimum_required(VERSION 3.20.0)

set(ENV{FW_BUNDLE} "com.hardwario.chester.clime")
set(ENV{FW_VERSION} "v1.0.0")
set(ENV{FW_NAME} "CHESTER Current")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(chester-current)

target_sources(app PRIVATE src/app_shell.c)
target_sources(app PRIVATE src/app_config.c)