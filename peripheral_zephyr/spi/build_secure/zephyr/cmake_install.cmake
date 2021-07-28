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
  set(CMAKE_OBJDUMP "C:/nordic/v1.6.0/toolchain/opt/bin/arm-none-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/arch/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/lib/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/soc/arm/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/boards/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/subsys/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/drivers/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/nrf/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/openthread/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/mcuboot/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/trusted-firmware-m/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/cjson/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/pelion-dm/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/cddl-gen/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/memfault-firmware-sdk/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/cmsis/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/canopennode/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/civetweb/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/fatfs/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/hal_nordic/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/st/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/libmetal/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/lvgl/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/mbedtls/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/mcumgr/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/open-amp/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/loramac-node/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/segger/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/tinycbor/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/tinycrypt/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/littlefs/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/mipi-sys-t/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/nrf_hw_models/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/TraceRecorder/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/nrfxlib/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/modules/connectedhomeip/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/kernel/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/cmake/flash/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/cmake/usage/cmake_install.cmake")
  include("C:/ncs/ncs_projects/peripheral/i2c/build_secure/zephyr/cmake/reports/cmake_install.cmake")

endif()

