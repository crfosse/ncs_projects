/* File generated by C:/Users/cafo/ncs/v1.3.0/nrf/scripts/partition_manager_output.py, do not modify */
#ifndef PM_CONFIG_H__
#define PM_CONFIG_H__
#include <autoconf.h>
#define PM_nrf5340pdk_nrf5340_cpuapp_APP_ADDRESS 0x0
#define PM_nrf5340pdk_nrf5340_cpuapp_APP_SIZE 0xfe000
#define PM_nrf5340pdk_nrf5340_cpuapp_APP_NAME app
#define PM_nrf5340pdk_nrf5340_cpuapp_APP_ID 0
#define PM_nrf5340pdk_nrf5340_cpuapp_app_ID PM_APP_ID
#define PM_0_LABEL nrf5340pdk_nrf5340_cpuapp_APP
#define PM_nrf5340pdk_nrf5340_cpuapp_APP_DEV_NAME "NRF_FLASH_DRV_NAME"
#define PM_nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE_ADDRESS 0xfe000
#define PM_nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE_SIZE 0x2000
#define PM_nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE_NAME settings_storage
#define PM_nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE_ID 1
#define PM_nrf5340pdk_nrf5340_cpuapp_settings_storage_ID PM_SETTINGS_STORAGE_ID
#define PM_1_LABEL nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE
#define PM_nrf5340pdk_nrf5340_cpuapp_SETTINGS_STORAGE_DEV_NAME "NRF_FLASH_DRV_NAME"
#define PM_nrf5340pdk_nrf5340_cpuapp_OTP_ADDRESS 0xff8100
#define PM_nrf5340pdk_nrf5340_cpuapp_OTP_SIZE 0x2fc
#define PM_nrf5340pdk_nrf5340_cpuapp_OTP_NAME otp
#define PM_nrf5340pdk_nrf5340_cpuapp_NUM 2
#define PM_nrf5340pdk_nrf5340_cpuapp_ALL_BY_SIZE "otp settings_storage app"
#define PM_APP_ADDRESS 0x1000000
#define PM_APP_SIZE 0x40000
#define PM_APP_NAME app
#define PM_APP_ID 2
#define PM_app_ID PM_APP_ID
#define PM_2_LABEL APP
#define PM_APP_DEV_NAME "NRF_FLASH_DRV_NAME"
#define PM_HCI_RPMSG_ADDRESS 0x1000000
#define PM_HCI_RPMSG_SIZE 0x40000
#define PM_HCI_RPMSG_NAME hci_rpmsg
#define PM_HCI_RPMSG_ID 3
#define PM_hci_rpmsg_ID PM_HCI_RPMSG_ID
#define PM_3_LABEL HCI_RPMSG
#define PM_HCI_RPMSG_DEV_NAME "NRF_FLASH_DRV_NAME"
#define PM_NUM 4
#define PM_ALL_BY_SIZE "hci_rpmsg app"
#define PM_ADDRESS 0x1000000
#define PM_SIZE 0x40000
#endif /* PM_CONFIG_H__ */