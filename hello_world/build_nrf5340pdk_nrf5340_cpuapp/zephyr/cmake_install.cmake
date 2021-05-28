# Install script for directory: C:/Users/crsfosse/ncs/v1.3.1/zephyr

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/arch/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/lib/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/soc/arm/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/boards/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/subsys/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/drivers/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/nrf/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/mcuboot/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/mcumgr/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/nrfxlib/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/cmsis/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/canopennode/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/civetweb/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/fatfs/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/nordic/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/st/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/libmetal/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/lvgl/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/mbedtls/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/open-amp/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/loramac-node/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/openthread/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/segger/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/tinycbor/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/tinycrypt/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/littlefs/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/mipi-sys-t/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/modules/nrf_hw_models/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/kernel/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/cmake/flash/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/cmake/usage/cmake_install.cmake")
  include("C:/Users/crsfosse/ncs/ncs_from_git/ncs_projects/hello_world/build_nrf5340pdk_nrf5340_cpuapp/zephyr/cmake/reports/cmake_install.cmake")

endif()

