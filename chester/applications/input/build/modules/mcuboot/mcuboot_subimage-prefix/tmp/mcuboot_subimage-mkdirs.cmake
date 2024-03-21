# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/frese/Documents/chester-app/bootloader/mcuboot/boot/zephyr"
  "/home/frese/Documents/chester-app/chester/applications/input/build/mcuboot"
  "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix"
  "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/tmp"
  "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/src/mcuboot_subimage-stamp"
  "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/src"
  "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/src/mcuboot_subimage-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/src/mcuboot_subimage-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/frese/Documents/chester-app/chester/applications/input/build/modules/mcuboot/mcuboot_subimage-prefix/src/mcuboot_subimage-stamp${cfgdir}") # cfgdir has leading slash
endif()
