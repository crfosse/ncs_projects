# Install script for directory: C:/ncs/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/cafo/ncs/v1.5.1/toolchain/opt/bin/arm-none-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/arch/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/lib/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/soc/arm/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/boards/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/drivers/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/nrf/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/mcuboot/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/trusted-firmware-m/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/openthread/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/cjson/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/pelion-dm/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/cddl-gen/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/memfault-firmware-sdk/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/cmsis/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/canopennode/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/civetweb/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/fatfs/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/hal_nordic/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/st/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/libmetal/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/lvgl/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/mbedtls/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/mcumgr/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/open-amp/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/loramac-node/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/segger/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/tinycbor/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/tinycrypt/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/littlefs/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/mipi-sys-t/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/nrf_hw_models/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/TraceRecorder/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/nrfxlib/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/modules/connectedhomeip/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/kernel/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/cmake/flash/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/cmake/usage/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/cmake/reports/cmake_install.cmake")

endif()

