# Install script for directory: C:/Users/cafo/ncs/my_ncs/ncs/zephyr

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
  set(CMAKE_OBJDUMP "C:/Users/cafo/ncs/v1.4.0/toolchain/opt/bin/arm-none-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/arch/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/lib/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/soc/arm/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/boards/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/subsys/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/drivers/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/nrf/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/mcuboot/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/mcumgr/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/nrfxlib/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/cmsis/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/canopennode/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/civetweb/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/fatfs/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/nordic/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/st/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/libmetal/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/lvgl/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/mbedtls/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/open-amp/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/loramac-node/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/openthread/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/segger/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/tinycbor/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/tinycrypt/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/littlefs/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/mipi-sys-t/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/modules/nrf_hw_models/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/kernel/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/cmake/flash/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/cmake/usage/cmake_install.cmake")
  include("C:/Users/cafo/ncs/my_ncs/ncs/ncs_projects/cellular/mqtt_work/build/spm/zephyr/cmake/reports/cmake_install.cmake")

endif()

