#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(mqtt_google_cloud)

if(NOT EXISTS ${APPLICATION_SOURCE_DIR}/src/private_info/key.c)
    message(FATAL_ERROR "!!!!!! Generate key file before continuing !!!!!!")
endif()

# NORDIC SDK APP START
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/gcloud.c)
target_sources(app PRIVATE src/private_info/key.c)
# NORDIC SDK APP END
zephyr_include_directories(src)

# Include application events and configuration headers
zephyr_library_include_directories(
  include
)