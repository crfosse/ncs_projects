# Install script for directory: C:/ncs/zephyr/subsys

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
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/debug/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/logging/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/bluetooth/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/fs/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/ipc/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/mgmt/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/net/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/random/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/storage/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/settings/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/fb/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/portability/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/pm/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/stats/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/task_wdt/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/testsuite/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/tracing/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/jwt/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/canbus/cmake_install.cmake")
  include("C:/ncs/ncs_projects/cellular/nrf_to_gcloud_with_ble/build_thingy91_nrf9160ns/zephyr/subsys/modbus/cmake_install.cmake")

endif()

