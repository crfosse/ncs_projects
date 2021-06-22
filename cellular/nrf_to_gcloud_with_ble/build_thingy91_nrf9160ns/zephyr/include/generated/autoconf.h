#define CONFIG_GCLOUD_PROJECT_NAME "nordic-91-test"
#define CONFIG_GCLOUD_REGION "europe-west1"
#define CONFIG_GCLOUD_REGISTRY_NAME "nrf9160_testing"
#define CONFIG_GCLOUD_DEVICE_NAME "nrf-352656101077215"
#define CONFIG_TEMP_DEV_NAME ""
#define CONFIG_USE_BME680_BSEC 1
#define CONFIG_BOSCH_BSEC_LIBRARY_PATH "C:/ncs/zephyr/../nrf/ext/BSEC_1.4.7.4_Generic_Release"
#define CONFIG_ENVIRONMENT_DATA_SEND_INTERVAL 30
#define CONFIG_ENVIRONMENT_DATA_BACKOFF_TIME 20
#define CONFIG_MQTT_MESSAGE_BUFFER_SIZE 1024
#define CONFIG_MQTT_PAYLOAD_BUFFER_SIZE 1024
#define CONFIG_GCLOUD_LOG_LEVEL 4
#define CONFIG_GPIO 1
#define CONFIG_SPI 1
#define CONFIG_I2C 1
#define CONFIG_UART_INTERRUPT_DRIVEN 1
#define CONFIG_NET_IPV6 1
#define CONFIG_BT_HCI_ACL_FLOW_CONTROL 1
#define CONFIG_BT_HCI_VS_EXT 1
#define CONFIG_BOARD "thingy91_nrf9160"
#define CONFIG_FLASH_LOAD_SIZE 0x0
#define CONFIG_FLASH_LOAD_OFFSET 0x0
#define CONFIG_BT_HCI_VS 1
#define CONFIG_SOC "nRF9160_SICA"
#define CONFIG_SOC_SERIES "nrf91"
#define CONFIG_NUM_IRQS 65
#define CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC 32768
#define CONFIG_HEAP_MEM_POOL_SIZE 16384
#define CONFIG_PM 1
#define CONFIG_SOC_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_CUSTOM_BUSY_WAIT 1
#define CONFIG_CLOCK_CONTROL 1
#define CONFIG_NRF_RTC_TIMER 1
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 32768
#define CONFIG_BUILD_OUTPUT_HEX 1
#define CONFIG_ROM_START_OFFSET 0x0
#define CONFIG_FLASH_SIZE 1024
#define CONFIG_FLASH_BASE_ADDRESS 0x0
#define CONFIG_TINYCRYPT 1
#define CONFIG_SERIAL 1
#define CONFIG_BOARD_THINGY91_NRF9160NS 1
#define CONFIG_MAIN_STACK_SIZE 8192
#define CONFIG_PRIVILEGED_STACK_SIZE 1024
#define CONFIG_ENTROPY_GENERATOR 1
#define CONFIG_LOG_DEFAULT_LEVEL 4
#define CONFIG_PM_PARTITION_SIZE_PROVISION 0x280
#define CONFIG_PM_PARTITION_SIZE_B0_IMAGE 0x8000
#define CONFIG_SB_VALIDATION_INFO_MAGIC 0x86518483
#define CONFIG_SB_VALIDATION_POINTER_MAGIC 0x6919b47e
#define CONFIG_SB_VALIDATION_INFO_CRYPTO_ID 1
#define CONFIG_SB_VALIDATION_INFO_VERSION 2
#define CONFIG_SB_VALIDATION_METADATA_OFFSET 0
#define CONFIG_SB_VALIDATE_FW_SIGNATURE 1
#define CONFIG_BT_MAX_CONN 1
#define CONFIG_BT_HCI_TX_STACK_SIZE 512
#define CONFIG_BT_RX_STACK_SIZE 1024
#define CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE 8192
#define CONFIG_BT_GATT_DM 1
#define CONFIG_BT_GATT_DM_MAX_ATTRS 35
#define CONFIG_BT_GATT_DM_LOG_LEVEL_INF 1
#define CONFIG_BT_GATT_DM_LOG_LEVEL 3
#define CONFIG_BT_SCAN 1
#define CONFIG_BT_SCAN_NAME_MAX_LEN 32
#define CONFIG_BT_SCAN_SHORT_NAME_MAX_LEN 32
#define CONFIG_BT_SCAN_FILTER_ENABLE 1
#define CONFIG_BT_SCAN_MANUFACTURER_DATA_MAX_LEN 32
#define CONFIG_BT_SCAN_UUID_CNT 0
#define CONFIG_BT_SCAN_NAME_CNT 0
#define CONFIG_BT_SCAN_SHORT_NAME_CNT 0
#define CONFIG_BT_SCAN_ADDRESS_CNT 0
#define CONFIG_BT_SCAN_APPEARANCE_CNT 0
#define CONFIG_BT_SCAN_MANUFACTURER_DATA_CNT 1
#define CONFIG_BT_SCAN_LOG_LEVEL_INF 1
#define CONFIG_BT_SCAN_LOG_LEVEL 3
#define CONFIG_SPM 1
#define CONFIG_SPM_BUILD_STRATEGY_FROM_SOURCE 1
#define CONFIG_SPM_SECURE_SERVICES 1
#define CONFIG_SPM_SERVICE_RNG 1
#define CONFIG_SPM_SERVICE_READ 1
#define CONFIG_SPM_SERVICE_FIND_FIRMWARE_INFO 1
#define CONFIG_ARM_ENTRY_VENEERS_LIB_NAME "spm/libspmsecureentries.a"
#define CONFIG_FW_INFO 1
#define CONFIG_FW_INFO_OFFSET 0x200
#define CONFIG_FW_INFO_FIRMWARE_VERSION 1
#define CONFIG_FW_INFO_MAGIC_COMMON 0x281ee6de
#define CONFIG_FW_INFO_MAGIC_FIRMWARE_INFO 0x8fcebb4c
#define CONFIG_FW_INFO_MAGIC_EXT_API 0xb845acea
#define CONFIG_FW_INFO_HARDWARE_ID 91
#define CONFIG_FW_INFO_VERSION 2
#define CONFIG_FW_INFO_CRYPTO_ID 0
#define CONFIG_FW_INFO_MAGIC_COMPATIBILITY_ID 0
#define CONFIG_FW_INFO_MAGIC_LEN 12
#define CONFIG_FW_INFO_VALID_VAL 0x9102FFFF
#define CONFIG_EXT_API_PROVIDE_EXT_API_UNUSED 1
#define CONFIG_MPSL_THREAD_COOP_PRIO 8
#define CONFIG_MPSL_SIGNAL_STACK_SIZE 1024
#define CONFIG_MPSL_TIMESLOT_SESSION_COUNT 0
#define CONFIG_MPSL_LOG_LEVEL_INF 1
#define CONFIG_MPSL_LOG_LEVEL 3
#define CONFIG_PARTITION_MANAGER_ENABLED 1
#define CONFIG_FLASH_MAP_CUSTOM 1
#define CONFIG_SRAM_SIZE 128
#define CONFIG_SRAM_BASE_ADDRESS 0x20020000
#define CONFIG_PM_PARTITION_SIZE_SETTINGS_STORAGE 0x2000
#define CONFIG_PM_SRAM_BASE 0x20000000
#define CONFIG_PM_SRAM_SIZE 0x40000
#define CONFIG_MGMT_FMFU_LOG_LEVEL_INF 1
#define CONFIG_MGMT_FMFU_LOG_LEVEL 3
#define CONFIG_BOOT_SIGNATURE_KEY_FILE ""
#define CONFIG_TFM_BOARD "C:/ncs/nrf/modules/tfm/tfm/boards/nrf9160"
#define CONFIG_AGPS_LOG_LEVEL_INF 1
#define CONFIG_AGPS_LOG_LEVEL 3
#define CONFIG_NRF_MODEM_LIB 1
#define CONFIG_NRF_MODEM_LIB_SYS_INIT 1
#define CONFIG_NRF91_SOCKET_BLOCK_LIMIT 2048
#define CONFIG_NRF_MODEM_LIB_SENDMSG_BUF_SIZE 128
#define CONFIG_NRF_MODEM_LIB_HEAP_SIZE 1024
#define CONFIG_NRF_MODEM_LIB_SHMEM_CTRL_SIZE 0x4e8
#define CONFIG_NRF_MODEM_LIB_SHMEM_TX_SIZE 8192
#define CONFIG_NRF_MODEM_LIB_SHMEM_RX_SIZE 8192
#define CONFIG_NRF_MODEM_LIB_SHMEM_TRACE_SIZE 0
#define CONFIG_NRF_MODEM_LIB_LOG_LEVEL_INF 1
#define CONFIG_NRF_MODEM_LIB_LOG_LEVEL 3
#define CONFIG_ADP536X 1
#define CONFIG_ADP536X_BUS_NAME "I2C_2"
#define CONFIG_AT_CMD 1
#define CONFIG_AT_CMD_SYS_INIT 1
#define CONFIG_AT_CMD_INIT_PRIORITY 40
#define CONFIG_AT_CMD_THREAD_PRIO 10
#define CONFIG_AT_CMD_THREAD_STACK_SIZE 1472
#define CONFIG_AT_CMD_QUEUE_LEN 16
#define CONFIG_AT_CMD_RESPONSE_MAX_LEN 2700
#define CONFIG_AT_CMD_LOG_LEVEL_INF 1
#define CONFIG_AT_CMD_LOG_LEVEL 3
#define CONFIG_LTE_LINK_CONTROL 1
#define CONFIG_LTE_LOCK_BANDS 1
#define CONFIG_LTE_LOCK_BAND_MASK "1000000010000001100010001110"
#define CONFIG_LTE_PSM_REQ_RPTAU "00000011"
#define CONFIG_LTE_PSM_REQ_RAT "00100001"
#define CONFIG_LTE_EDRX_REQ_VALUE_LTE_M "1001"
#define CONFIG_LTE_EDRX_REQ_VALUE_NBIOT "1001"
#define CONFIG_LTE_PTW_VALUE_LTE_M ""
#define CONFIG_LTE_PTW_VALUE_NBIOT ""
#define CONFIG_LTE_NETWORK_MODE_LTE_M 1
#define CONFIG_LTE_MODE_PREFERENCE_AUTO 1
#define CONFIG_LTE_MODE_PREFERENCE 0
#define CONFIG_LTE_RAI_REQ_VALUE "0"
#define CONFIG_LTE_NETWORK_USE_FALLBACK 1
#define CONFIG_LTE_NETWORK_TIMEOUT 600
#define CONFIG_LTE_LC_TAU_PRE_WARNING_TIME_MS 5000
#define CONFIG_LTE_LC_TAU_PRE_WARNING_THRESHOLD_MS 1200000
#define CONFIG_LTE_NEIGHBOR_CELLS_MAX 10
#define CONFIG_LTE_LC_MODEM_SLEEP_PRE_WARNING_TIME_MS 5000
#define CONFIG_LTE_LC_MODEM_SLEEP_NOTIFICATIONS_THRESHOLD_MS 1200000
#define CONFIG_LTE_LINK_CONTROL_LOG_LEVEL_DBG 1
#define CONFIG_LTE_LINK_CONTROL_LOG_LEVEL 4
#define CONFIG_NRF_SPU_FLASH_REGION_SIZE 0x8000
#define CONFIG_FPROTECT_BLOCK_SIZE 0x8000
#define CONFIG_AT_NOTIF 1
#define CONFIG_AT_NOTIF_SYS_INIT 1
#define CONFIG_AT_NOTIF_LOG_LEVEL_INF 1
#define CONFIG_AT_NOTIF_LOG_LEVEL 3
#define CONFIG_AT_HOST_LIBRARY 1
#define CONFIG_AT_HOST_UART_0 1
#define CONFIG_AT_HOST_UART 0
#define CONFIG_AT_HOST_UART_INIT_TIMEOUT 500
#define CONFIG_CR_TERMINATION 1
#define CONFIG_AT_HOST_TERMINATION 1
#define CONFIG_AT_HOST_CMD_MAX_LEN 4096
#define CONFIG_AT_HOST_THREAD_PRIO 10
#define CONFIG_AT_HOST_LOG_LEVEL_INF 1
#define CONFIG_AT_HOST_LOG_LEVEL 3
#define CONFIG_AT_CMD_PARSER 1
#define CONFIG_MODEM_INFO 1
#define CONFIG_MODEM_INFO_MAX_AT_PARAMS_RSP 10
#define CONFIG_MODEM_INFO_BUFFER_SIZE 128
#define CONFIG_MODEM_INFO_ADD_NETWORK 1
#define CONFIG_MODEM_INFO_ADD_DATE_TIME 1
#define CONFIG_MODEM_INFO_ADD_SIM 1
#define CONFIG_MODEM_INFO_ADD_SIM_ICCID 1
#define CONFIG_MODEM_INFO_ADD_SIM_IMSI 1
#define CONFIG_MODEM_INFO_ADD_DEVICE 1
#define CONFIG_MODEM_INFO_ADD_BOARD 1
#define CONFIG_RESET_ON_FATAL_ERROR 1
#define CONFIG_FATAL_ERROR_LOG_LEVEL_INF 1
#define CONFIG_FATAL_ERROR_LOG_LEVEL 3
#define CONFIG_MODEM_KEY_MGMT 1
#define CONFIG_MODEM_KEY_MGMT_LOG_LEVEL_INF 1
#define CONFIG_MODEM_KEY_MGMT_LOG_LEVEL 3
#define CONFIG_DATE_TIME 1
#define CONFIG_DATE_TIME_UPDATE_INTERVAL_SECONDS 0
#define CONFIG_DATE_TIME_MODEM 1
#define CONFIG_DATE_TIME_NTP 1
#define CONFIG_DATE_TIME_THREAD_SIZE 1024
#define CONFIG_DATE_TIME_NTP_QUERY_TIME_SECONDS 5
#define CONFIG_DATE_TIME_LOG_LEVEL_DBG 1
#define CONFIG_DATE_TIME_LOG_LEVEL 4
#define CONFIG_HW_UNIQUE_KEY_PARTITION_SIZE 0x0
#define CONFIG_ENTROPY_CC3XX 1
#define CONFIG_NRF_SW_LPUART 1
#define CONFIG_NRF_SW_LPUART_INIT_PRIORITY 45
#define CONFIG_NRF_SW_LPUART_HFXO_ON_RX 1
#define CONFIG_NRF_SW_LPUART_MAX_PACKET_SIZE 128
#define CONFIG_NRF_SW_LPUART_DEFAULT_TX_TIMEOUT 1000
#define CONFIG_NRF_SW_LPUART_INT_DRIVEN 1
#define CONFIG_NRF_SW_LPUART_INT_DRV_TX_BUF_SIZE 128
#define CONFIG_NRF_SW_LPUART_LOG_LEVEL_INF 1
#define CONFIG_NRF_SW_LPUART_LOG_LEVEL 3
#define CONFIG_ZEPHYR_NRF_MODULE 1
#define CONFIG_DT_FLASH_WRITE_BLOCK_SIZE 4
#define CONFIG_ZEPHYR_MCUBOOT_MODULE 1
#define CONFIG_ZEPHYR_TRUSTED_FIRMWARE_M_MODULE 1
#define CONFIG_CJSON_LIB 1
#define CONFIG_ZEPHYR_CJSON_MODULE 1
#define CONFIG_NEWLIB_LIBC_FLOAT_PRINTF 1
#define CONFIG_ZEPHYR_PELION_DM_MODULE 1
#define CONFIG_ZEPHYR_CDDL_GEN_MODULE 1
#define CONFIG_ZEPHYR_MEMFAULT_FIRMWARE_SDK_MODULE 1
#define CONFIG_ZEPHYR_HAL_NORDIC_MODULE 1
#define CONFIG_HAS_NRFX 1
#define CONFIG_NRFX_CLOCK 1
#define CONFIG_NRFX_CLOCK_LFXO_TWO_STAGE_ENABLED 1
#define CONFIG_NRFX_DPPI 1
#define CONFIG_NRFX_GPIOTE 1
#define CONFIG_NRFX_IPC 1
#define CONFIG_NRFX_NVMC 1
#define CONFIG_NRFX_SPIM 1
#define CONFIG_NRFX_SPIM3 1
#define CONFIG_NRFX_TIMER 1
#define CONFIG_NRFX_TIMER2 1
#define CONFIG_NRFX_TWIM 1
#define CONFIG_NRFX_TWIM2 1
#define CONFIG_ZEPHYR_MBEDTLS_MODULE 1
#define CONFIG_MBEDTLS_BUILTIN 1
#define CONFIG_ZEPHYR_TRACERECORDER_MODULE 1
#define CONFIG_NRF_MODEM 1
#define CONFIG_NRF_MODEM_LINK_BINARY 1
#define CONFIG_NRF_MODEM_SHMEM_CTRL_SIZE 0x4e8
#define CONFIG_NRF_802154_SOURCE_NRFXLIB 1
#define CONFIG_ZEPHYR_NRFXLIB_MODULE 1
#define CONFIG_ZEPHYR_CONNECTEDHOMEIP_MODULE 1
#define CONFIG_HAS_CMSIS_CORE 1
#define CONFIG_HAS_CMSIS_CORE_M 1
#define CONFIG_TINYCRYPT_CTR_PRNG 1
#define CONFIG_TINYCRYPT_SHA256 1
#define CONFIG_TINYCRYPT_SHA256_HMAC 1
#define CONFIG_TINYCRYPT_SHA256_HMAC_PRNG 1
#define CONFIG_TINYCRYPT_ECC_DSA 1
#define CONFIG_TINYCRYPT_AES 1
#define CONFIG_TINYCRYPT_AES_CMAC 1
#define CONFIG_BOARD_NRF52840_GPIO_RESET 1
#define CONFIG_BOARD_LOG_LEVEL_INF 1
#define CONFIG_BOARD_LOG_LEVEL 3
#define CONFIG_SOC_SERIES_NRF91X 1
#define CONFIG_CPU_HAS_ARM_MPU 1
#define CONFIG_CPU_HAS_NRF_IDAU 1
#define CONFIG_NRF_SPU_RAM_REGION_SIZE 0x2000
#define CONFIG_SOC_FAMILY "nordic_nrf"
#define CONFIG_SOC_FAMILY_NRF 1
#define CONFIG_HAS_HW_NRF_CC310 1
#define CONFIG_HAS_HW_NRF_CLOCK 1
#define CONFIG_HAS_HW_NRF_DPPIC 1
#define CONFIG_HAS_HW_NRF_EGU0 1
#define CONFIG_HAS_HW_NRF_EGU1 1
#define CONFIG_HAS_HW_NRF_EGU2 1
#define CONFIG_HAS_HW_NRF_EGU3 1
#define CONFIG_HAS_HW_NRF_EGU4 1
#define CONFIG_HAS_HW_NRF_EGU5 1
#define CONFIG_HAS_HW_NRF_GPIO0 1
#define CONFIG_HAS_HW_NRF_GPIOTE 1
#define CONFIG_HAS_HW_NRF_I2S 1
#define CONFIG_HAS_HW_NRF_IPC 1
#define CONFIG_HAS_HW_NRF_NVMC_PE 1
#define CONFIG_HAS_HW_NRF_PDM 1
#define CONFIG_HAS_HW_NRF_POWER 1
#define CONFIG_HAS_HW_NRF_PWM0 1
#define CONFIG_HAS_HW_NRF_PWM1 1
#define CONFIG_HAS_HW_NRF_PWM2 1
#define CONFIG_HAS_HW_NRF_PWM3 1
#define CONFIG_HAS_HW_NRF_RTC0 1
#define CONFIG_HAS_HW_NRF_RTC1 1
#define CONFIG_HAS_HW_NRF_SAADC 1
#define CONFIG_HAS_HW_NRF_SPIM0 1
#define CONFIG_HAS_HW_NRF_SPIM1 1
#define CONFIG_HAS_HW_NRF_SPIM2 1
#define CONFIG_HAS_HW_NRF_SPIM3 1
#define CONFIG_HAS_HW_NRF_SPIS0 1
#define CONFIG_HAS_HW_NRF_SPIS1 1
#define CONFIG_HAS_HW_NRF_SPIS2 1
#define CONFIG_HAS_HW_NRF_SPIS3 1
#define CONFIG_HAS_HW_NRF_SPU 1
#define CONFIG_HAS_HW_NRF_TIMER0 1
#define CONFIG_HAS_HW_NRF_TIMER1 1
#define CONFIG_HAS_HW_NRF_TIMER2 1
#define CONFIG_HAS_HW_NRF_TWIM0 1
#define CONFIG_HAS_HW_NRF_TWIM1 1
#define CONFIG_HAS_HW_NRF_TWIM2 1
#define CONFIG_HAS_HW_NRF_TWIM3 1
#define CONFIG_HAS_HW_NRF_TWIS0 1
#define CONFIG_HAS_HW_NRF_TWIS1 1
#define CONFIG_HAS_HW_NRF_TWIS2 1
#define CONFIG_HAS_HW_NRF_TWIS3 1
#define CONFIG_HAS_HW_NRF_UARTE0 1
#define CONFIG_HAS_HW_NRF_UARTE1 1
#define CONFIG_HAS_HW_NRF_UARTE2 1
#define CONFIG_HAS_HW_NRF_UARTE3 1
#define CONFIG_HAS_HW_NRF_WDT 1
#define CONFIG_NRF_HW_RTC1_RESERVED 1
#define CONFIG_NRF_ENABLE_ICACHE 1
#define CONFIG_SOC_NRF9160 1
#define CONFIG_SOC_NRF9160_SICA 1
#define CONFIG_SOC_LOG_LEVEL_INF 1
#define CONFIG_SOC_LOG_LEVEL 3
#define CONFIG_SOC_COMPATIBLE_NRF 1
#define CONFIG_ARCH "arm"
#define CONFIG_CPU_CORTEX 1
#define CONFIG_CPU_CORTEX_M 1
#define CONFIG_ISA_THUMB2 1
#define CONFIG_ASSEMBLER_ISA_THUMB2 1
#define CONFIG_COMPILER_ISA_THUMB2 1
#define CONFIG_STACK_ALIGN_DOUBLE_WORD 1
#define CONFIG_PLATFORM_SPECIFIC_INIT 1
#define CONFIG_FAULT_DUMP 2
#define CONFIG_BUILTIN_STACK_GUARD 1
#define CONFIG_ARM_STACK_PROTECTION 1
#define CONFIG_ARM_NONSECURE_FIRMWARE 1
#define CONFIG_CPU_CORTEX_M33 1
#define CONFIG_CPU_CORTEX_M_HAS_SYSTICK 1
#define CONFIG_CPU_CORTEX_M_HAS_DWT 1
#define CONFIG_CPU_CORTEX_M_HAS_BASEPRI 1
#define CONFIG_CPU_CORTEX_M_HAS_VTOR 1
#define CONFIG_CPU_CORTEX_M_HAS_SPLIM 1
#define CONFIG_CPU_CORTEX_M_HAS_PROGRAMMABLE_FAULT_PRIOS 1
#define CONFIG_CPU_CORTEX_M_HAS_CMSE 1
#define CONFIG_ARMV7_M_ARMV8_M_MAINLINE 1
#define CONFIG_ARMV8_M_MAINLINE 1
#define CONFIG_ARMV8_M_SE 1
#define CONFIG_ARMV7_M_ARMV8_M_FP 1
#define CONFIG_ARMV8_M_DSP 1
#define CONFIG_GEN_ISR_TABLES 1
#define CONFIG_TEST_EXTRA_STACKSIZE 0
#define CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_DETECTION_NONE 1
#define CONFIG_ARM_TRUSTZONE_M 1
#define CONFIG_ARM_FIRMWARE_USES_SECURE_ENTRY_FUNCS 1
#define CONFIG_GEN_IRQ_VECTOR_TABLE 1
#define CONFIG_ARM_MPU 1
#define CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE 32
#define CONFIG_CUSTOM_SECTION_MIN_ALIGN_SIZE 32
#define CONFIG_ARM 1
#define CONFIG_ARCH_IS_SET 1
#define CONFIG_ARCH_LOG_LEVEL_INF 1
#define CONFIG_ARCH_LOG_LEVEL 3
#define CONFIG_MPU_LOG_LEVEL_INF 1
#define CONFIG_MPU_LOG_LEVEL 3
#define CONFIG_TRUSTED_EXECUTION_NONSECURE 1
#define CONFIG_HW_STACK_PROTECTION 1
#define CONFIG_KOBJECT_TEXT_AREA 256
#define CONFIG_KOBJECT_DATA_AREA_RESERVE_EXTRA_PERCENT 100
#define CONFIG_KOBJECT_RODATA_AREA_EXTRA_BYTES 16
#define CONFIG_GEN_PRIV_STACKS 1
#define CONFIG_GEN_SW_ISR_TABLE 1
#define CONFIG_ARCH_SW_ISR_TABLE_ALIGN 0
#define CONFIG_GEN_IRQ_START_VECTOR 0
#define CONFIG_ARCH_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_TRUSTED_EXECUTION 1
#define CONFIG_ARCH_HAS_STACK_PROTECTION 1
#define CONFIG_ARCH_HAS_USERSPACE 1
#define CONFIG_ARCH_HAS_EXECUTABLE_PAGE_BIT 1
#define CONFIG_ARCH_HAS_RAMFUNC_SUPPORT 1
#define CONFIG_ARCH_HAS_NESTED_EXCEPTION_DETECTION 1
#define CONFIG_ARCH_SUPPORTS_COREDUMP 1
#define CONFIG_ARCH_SUPPORTS_ARCH_HW_INIT 1
#define CONFIG_ARCH_HAS_EXTRA_EXCEPTION_INFO 1
#define CONFIG_ARCH_HAS_THREAD_LOCAL_STORAGE 1
#define CONFIG_ARCH_HAS_THREAD_ABORT 1
#define CONFIG_CPU_HAS_TEE 1
#define CONFIG_CPU_HAS_FPU 1
#define CONFIG_CPU_HAS_MPU 1
#define CONFIG_MPU 1
#define CONFIG_MPU_REQUIRES_NON_OVERLAPPING_REGIONS 1
#define CONFIG_MPU_GAP_FILLING 1
#define CONFIG_SRAM_REGION_PERMISSIONS 1
#define CONFIG_TOOLCHAIN_HAS_BUILTIN_FFS 1
#define CONFIG_KERNEL_LOG_LEVEL_INF 1
#define CONFIG_KERNEL_LOG_LEVEL 3
#define CONFIG_MULTITHREADING 1
#define CONFIG_NUM_COOP_PRIORITIES 16
#define CONFIG_NUM_PREEMPT_PRIORITIES 15
#define CONFIG_MAIN_THREAD_PRIORITY 0
#define CONFIG_COOP_ENABLED 1
#define CONFIG_PREEMPT_ENABLED 1
#define CONFIG_PRIORITY_CEILING 0
#define CONFIG_NUM_METAIRQ_PRIORITIES 0
#define CONFIG_IDLE_STACK_SIZE 320
#define CONFIG_ISR_STACK_SIZE 2048
#define CONFIG_THREAD_STACK_INFO 1
#define CONFIG_ERRNO 1
#define CONFIG_SCHED_DUMB 1
#define CONFIG_WAITQ_DUMB 1
#define CONFIG_BOOT_BANNER 1
#define CONFIG_BOOT_DELAY 0
#define CONFIG_SYSTEM_WORKQUEUE_PRIORITY -1
#define CONFIG_ATOMIC_OPERATIONS_BUILTIN 1
#define CONFIG_TIMESLICING 1
#define CONFIG_TIMESLICE_SIZE 0
#define CONFIG_TIMESLICE_PRIORITY 0
#define CONFIG_POLL 1
#define CONFIG_NUM_MBOX_ASYNC_MSGS 10
#define CONFIG_NUM_PIPE_ASYNC_MSGS 10
#define CONFIG_KERNEL_MEM_POOL 1
#define CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN 1
#define CONFIG_SWAP_NONATOMIC 1
#define CONFIG_SYS_CLOCK_EXISTS 1
#define CONFIG_TIMEOUT_64BIT 1
#define CONFIG_XIP 1
#define CONFIG_KERNEL_INIT_PRIORITY_OBJECTS 30
#define CONFIG_KERNEL_INIT_PRIORITY_DEFAULT 40
#define CONFIG_KERNEL_INIT_PRIORITY_DEVICE 50
#define CONFIG_APPLICATION_INIT_PRIORITY 90
#define CONFIG_STACK_POINTER_RANDOM 0
#define CONFIG_MP_NUM_CPUS 1
#define CONFIG_TICKLESS_KERNEL 1
#define CONFIG_HAS_DTS 1
#define CONFIG_HAS_DTS_GPIO 1
#define CONFIG_BT_UART 1
#define CONFIG_BT_H4 1
#define CONFIG_BT_UART_ON_DEV_NAME "LPUART"
#define CONFIG_UART_CONSOLE_ON_DEV_NAME "UART_0"
#define CONFIG_CONSOLE 1
#define CONFIG_CONSOLE_INPUT_MAX_LINE_LEN 128
#define CONFIG_CONSOLE_HAS_DRIVER 1
#define CONFIG_UART_CONSOLE 1
#define CONFIG_UART_CONSOLE_INIT_PRIORITY 60
#define CONFIG_UART_CONSOLE_INPUT_EXPIRED 1
#define CONFIG_UART_CONSOLE_INPUT_EXPIRED_TIMEOUT 15000
#define CONFIG_UART_CONSOLE_LOG_LEVEL_INF 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL 3
#define CONFIG_HAS_SEGGER_RTT 1
#define CONFIG_SERIAL_HAS_DRIVER 1
#define CONFIG_SERIAL_SUPPORT_ASYNC 1
#define CONFIG_SERIAL_SUPPORT_INTERRUPT 1
#define CONFIG_UART_ASYNC_API 1
#define CONFIG_UART_NRFX 1
#define CONFIG_UART_0_NRF_UARTE 1
#define CONFIG_UART_0_ENHANCED_POLL_OUT 1
#define CONFIG_UART_0_INTERRUPT_DRIVEN 1
#define CONFIG_UART_0_NRF_TX_BUFFER_SIZE 32
#define CONFIG_UART_1_NRF_UARTE 1
#define CONFIG_UART_1_ASYNC 1
#define CONFIG_UART_1_ENHANCED_POLL_OUT 1
#define CONFIG_UART_1_NRF_TX_BUFFER_SIZE 32
#define CONFIG_UART_1_NRF_HW_ASYNC 1
#define CONFIG_UART_1_NRF_HW_ASYNC_TIMER 2
#define CONFIG_UARTE_NRF_HW_ASYNC 1
#define CONFIG_UART_ENHANCED_POLL_OUT 1
#define CONFIG_NRF_UARTE_PERIPHERAL 1
#define CONFIG_APIC_TIMER_IRQ_PRIORITY 4
#define CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT 0
#define CONFIG_SYSTEM_CLOCK_WAIT_FOR_STABILITY 1
#define CONFIG_SYSTEM_CLOCK_DISABLE 1
#define CONFIG_SYSTEM_CLOCK_INIT_PRIORITY 0
#define CONFIG_TICKLESS_CAPABLE 1
#define CONFIG_ENTROPY_HAS_DRIVER 1
#define CONFIG_GPIO_LOG_LEVEL_INF 1
#define CONFIG_GPIO_LOG_LEVEL 3
#define CONFIG_GPIO_NRFX 1
#define CONFIG_GPIO_NRF_INIT_PRIORITY 40
#define CONFIG_GPIO_NRF_P0 1
#define CONFIG_GPIO_NRF_INT_EDGE_USING_GPIOTE 1
#define CONFIG_SPI_INIT_PRIORITY 70
#define CONFIG_SPI_LOG_LEVEL_INF 1
#define CONFIG_SPI_LOG_LEVEL 3
#define CONFIG_SPI_NRFX 1
#define CONFIG_SPI_3_NRF_SPIM 1
#define CONFIG_SPI_3_NRF_ORC 0xff
#define CONFIG_SPI_NRFX_RAM_BUFFER_SIZE 8
#define CONFIG_I2C_NRFX 1
#define CONFIG_I2C_2_NRF_TWIM 1
#define CONFIG_I2C_INIT_PRIORITY 60
#define CONFIG_I2C_LOG_LEVEL_INF 1
#define CONFIG_I2C_LOG_LEVEL 3
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL_INF 1
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL 3
#define CONFIG_CLOCK_CONTROL_NRF 1
#define CONFIG_CLOCK_CONTROL_NRF_K32SRC_XTAL 1
#define CONFIG_CLOCK_CONTROL_NRF_K32SRC_50PPM 1
#define CONFIG_CLOCK_CONTROL_NRF_ACCURACY 50
#define CONFIG_NEWLIB_LIBC 1
#define CONFIG_HAS_NEWLIB_LIBC_NANO 1
#define CONFIG_NEWLIB_LIBC_NANO 1
#define CONFIG_STDOUT_CONSOLE 1
#define CONFIG_JSON_LIBRARY 1
#define CONFIG_SYS_HEAP_ALLOC_LOOPS 3
#define CONFIG_MPSC_PBUF 1
#define CONFIG_REBOOT 1
#define CONFIG_CBPRINTF_COMPLETE 1
#define CONFIG_CBPRINTF_FULL_INTEGRAL 1
#define CONFIG_CBPRINTF_N_SPECIFIER 1
#define CONFIG_POSIX_MAX_FDS 4
#define CONFIG_MAX_TIMER_COUNT 5
#define CONFIG_BT 1
#define CONFIG_BT_LOG_LEVEL_INF 1
#define CONFIG_BT_LOG_LEVEL 3
#define CONFIG_BT_HCI 1
#define CONFIG_BT_CENTRAL 1
#define CONFIG_BT_OBSERVER 1
#define CONFIG_BT_CONN 1
#define CONFIG_BT_PHY_UPDATE 1
#define CONFIG_BT_DATA_LEN_UPDATE 1
#define CONFIG_BT_BUF_ACL_TX_SIZE 27
#define CONFIG_BT_BUF_ACL_TX_COUNT 3
#define CONFIG_BT_BUF_ACL_RX_SIZE 27
#define CONFIG_BT_BUF_ACL_RX_COUNT 3
#define CONFIG_BT_BUF_EVT_RX_SIZE 68
#define CONFIG_BT_BUF_EVT_RX_COUNT 3
#define CONFIG_BT_BUF_EVT_DISCARDABLE_SIZE 43
#define CONFIG_BT_BUF_EVT_DISCARDABLE_COUNT 3
#define CONFIG_BT_BUF_CMD_TX_SIZE 65
#define CONFIG_BT_BUF_CMD_TX_COUNT 2
#define CONFIG_BT_WAIT_NOP 1
#define CONFIG_BT_ASSERT 1
#define CONFIG_BT_ASSERT_VERBOSE 1
#define CONFIG_BT_DEBUG_NONE 1
#define CONFIG_BT_HCI_HOST 1
#define CONFIG_BT_HCI_ECC_STACK_SIZE 1140
#define CONFIG_BT_HCI_TX_PRIO 7
#define CONFIG_BT_HCI_RESERVE 0
#define CONFIG_BT_RECV_IS_RX_THREAD 1
#define CONFIG_BT_RX_PRIO 8
#define CONFIG_BT_DRIVER_RX_HIGH_PRIO 6
#define CONFIG_BT_HOST_CRYPTO 1
#define CONFIG_BT_CONN_TX_MAX 3
#define CONFIG_BT_AUTO_PHY_UPDATE 1
#define CONFIG_BT_AUTO_DATA_LEN_UPDATE 1
#define CONFIG_BT_L2CAP_TX_BUF_COUNT 3
#define CONFIG_BT_L2CAP_TX_FRAG_COUNT 2
#define CONFIG_BT_L2CAP_TX_MTU 247
#define CONFIG_BT_ATT_ENFORCE_FLOW 1
#define CONFIG_BT_ATT_PREPARE_COUNT 0
#define CONFIG_BT_GATT_SERVICE_CHANGED 1
#define CONFIG_BT_GATT_CACHING 1
#define CONFIG_BT_GATT_CLIENT 1
#define CONFIG_BT_GATT_READ_MULTIPLE 1
#define CONFIG_BT_MAX_PAIRED 0
#define CONFIG_BT_CREATE_CONN_TIMEOUT 3
#define CONFIG_BT_CONN_PARAM_UPDATE_TIMEOUT 5000
#define CONFIG_BT_BACKGROUND_SCAN_INTERVAL 2048
#define CONFIG_BT_BACKGROUND_SCAN_WINDOW 18
#define CONFIG_BT_DEVICE_NAME "Zephyr"
#define CONFIG_BT_DEVICE_APPEARANCE 0
#define CONFIG_BT_ID_MAX 1
#define CONFIG_BT_COMPANY_ID 0x05F1
#define CONFIG_PRINTK 1
#define CONFIG_EARLY_CONSOLE 1
#define CONFIG_ASSERT 1
#define CONFIG_ASSERT_LEVEL 2
#define CONFIG_SPIN_VALIDATE 1
#define CONFIG_ASSERT_VERBOSE 1
#define CONFIG_JWT 1
#define CONFIG_JWT_SIGN_ECDSA 1
#define CONFIG_LOG 1
#define CONFIG_LOG_MODE_DEFERRED 1
#define CONFIG_LOG_OVERRIDE_LEVEL 0
#define CONFIG_LOG_MAX_LEVEL 4
#define CONFIG_LOG_FUNC_NAME_PREFIX_DBG 1
#define CONFIG_LOG_BACKEND_SHOW_COLOR 1
#define CONFIG_LOG_BACKEND_FORMAT_TIMESTAMP 1
#define CONFIG_LOG_MODE_OVERFLOW 1
#define CONFIG_LOG_PROCESS_TRIGGER_THRESHOLD 10
#define CONFIG_LOG_PROCESS_THREAD 1
#define CONFIG_LOG_PROCESS_THREAD_SLEEP_MS 1000
#define CONFIG_LOG_PROCESS_THREAD_STACK_SIZE 768
#define CONFIG_LOG_BUFFER_SIZE 1024
#define CONFIG_LOG_DETECT_MISSED_STRDUP 1
#define CONFIG_LOG_STRDUP_MAX_STRING 256
#define CONFIG_LOG_STRDUP_BUF_COUNT 12
#define CONFIG_LOG_BACKEND_UART 1
#define CONFIG_LOG_BACKEND_UART_OUTPUT_TEXT 1
#define CONFIG_LOG_DOMAIN_ID 0
#define CONFIG_LOG2_USE_VLA 1
#define CONFIG_NET_BUF 1
#define CONFIG_NET_BUF_USER_DATA_SIZE 4
#define CONFIG_NET_BUF_LOG_LEVEL_INF 1
#define CONFIG_NET_BUF_LOG_LEVEL 3
#define CONFIG_NETWORKING 1
#define CONFIG_NET_INIT_PRIO 90
#define CONFIG_NET_IF_MAX_IPV6_COUNT 1
#define CONFIG_NET_IF_UNICAST_IPV6_ADDR_COUNT 2
#define CONFIG_NET_IF_MCAST_IPV6_ADDR_COUNT 3
#define CONFIG_NET_IF_IPV6_PREFIX_COUNT 2
#define CONFIG_NET_INITIAL_HOP_LIMIT 64
#define CONFIG_NET_IPV6_MAX_NEIGHBORS 8
#define CONFIG_NET_IPV6_MLD 1
#define CONFIG_NET_IPV6_NBR_CACHE 1
#define CONFIG_NET_IPV6_ND 1
#define CONFIG_NET_IPV6_DAD 1
#define CONFIG_NET_IPV6_RA_RDNSS 1
#define CONFIG_NET_IPV6_LOG_LEVEL 0
#define CONFIG_NET_ICMPV6_LOG_LEVEL 0
#define CONFIG_NET_IPV6_NBR_CACHE_LOG_LEVEL 0
#define CONFIG_NET_TC_TX_COUNT 0
#define CONFIG_NET_TC_RX_COUNT 1
#define CONFIG_NET_TC_THREAD_COOPERATIVE 1
#define CONFIG_NET_TC_NUM_PRIORITIES 16
#define CONFIG_NET_TC_MAPPING_STRICT 1
#define CONFIG_NET_TX_DEFAULT_PRIORITY 1
#define CONFIG_NET_RX_DEFAULT_PRIORITY 0
#define CONFIG_NET_IP_ADDR_CHECK 1
#define CONFIG_NET_MAX_ROUTERS 1
#define CONFIG_NET_ROUTE 1
#define CONFIG_NET_MAX_ROUTES 8
#define CONFIG_NET_MAX_NEXTHOPS 8
#define CONFIG_NET_UDP 1
#define CONFIG_NET_UDP_CHECKSUM 1
#define CONFIG_NET_UDP_LOG_LEVEL 0
#define CONFIG_NET_MAX_CONN 4
#define CONFIG_NET_MAX_CONTEXTS 6
#define CONFIG_NET_CONTEXT_SYNC_RECV 1
#define CONFIG_NET_CONTEXT_CHECK 1
#define CONFIG_NET_PKT_RX_COUNT 4
#define CONFIG_NET_PKT_TX_COUNT 4
#define CONFIG_NET_BUF_RX_COUNT 16
#define CONFIG_NET_BUF_TX_COUNT 16
#define CONFIG_NET_BUF_FIXED_DATA_SIZE 1
#define CONFIG_NET_BUF_DATA_SIZE 128
#define CONFIG_NET_DEFAULT_IF_FIRST 1
#define CONFIG_NET_TX_STACK_SIZE 1200
#define CONFIG_NET_RX_STACK_SIZE 1500
#define CONFIG_NET_PKT_LOG_LEVEL 0
#define CONFIG_NET_DEBUG_NET_PKT_EXTERNALS 0
#define CONFIG_NET_CORE_LOG_LEVEL 0
#define CONFIG_NET_IF_LOG_LEVEL 0
#define CONFIG_NET_TC_LOG_LEVEL 0
#define CONFIG_NET_UTILS_LOG_LEVEL 0
#define CONFIG_NET_CONTEXT_LOG_LEVEL 0
#define CONFIG_NET_CONN_LOG_LEVEL 0
#define CONFIG_NET_ROUTE_LOG_LEVEL 0
#define CONFIG_MQTT_LIB 1
#define CONFIG_MQTT_LOG_LEVEL 0
#define CONFIG_MQTT_KEEPALIVE 60
#define CONFIG_MQTT_LIB_TLS 1
#define CONFIG_MQTT_CLEAN_SESSION 1
#define CONFIG_NET_HTTP_LOG_LEVEL 0
#define CONFIG_SNTP 1
#define CONFIG_SNTP_LOG_LEVEL 0
#define CONFIG_NET_CONFIG_AUTO_INIT 1
#define CONFIG_NET_CONFIG_INIT_PRIO 95
#define CONFIG_NET_CONFIG_INIT_TIMEOUT 30
#define CONFIG_NET_CONFIG_LOG_LEVEL 0
#define CONFIG_NET_SOCKETS 1
#define CONFIG_NET_SOCKETS_POSIX_NAMES 1
#define CONFIG_NET_SOCKETS_POLL_MAX 3
#define CONFIG_NET_SOCKETS_CONNECT_TIMEOUT 3000
#define CONFIG_NET_SOCKETS_TLS_SET_MAX_FRAGMENT_LENGTH 1
#define CONFIG_NET_SOCKETS_OFFLOAD 1
#define CONFIG_NET_SOCKETS_OFFLOAD_TLS 1
#define CONFIG_NET_SOCKETS_LOG_LEVEL 0
#define CONFIG_PM_POLICY_RESIDENCY 1
#define CONFIG_PM_POLICY_RESIDENCY_DEFAULT 1
#define CONFIG_PM_LOG_LEVEL_INF 1
#define CONFIG_PM_LOG_LEVEL 3
#define CONFIG_ENTROPY_DEVICE_RANDOM_GENERATOR 1
#define CONFIG_CSPRING_ENABLED 1
#define CONFIG_HARDWARE_DEVICE_CS_GENERATOR 1
#define CONFIG_SETTINGS 1
#define CONFIG_SETTINGS_LOG_LEVEL_INF 1
#define CONFIG_SETTINGS_LOG_LEVEL 3
#define CONFIG_SETTINGS_DYNAMIC_HANDLERS 1
#define CONFIG_SETTINGS_NONE 1
#define CONFIG_TOOLCHAIN_GNUARMEMB 1
#define CONFIG_LINKER_ORPHAN_SECTION_WARN 1
#define CONFIG_HAS_FLASH_LOAD_OFFSET 1
#define CONFIG_KERNEL_ENTRY "__start"
#define CONFIG_LINKER_SORT_BY_ALIGNMENT 1
#define CONFIG_SRAM_OFFSET 0x0
#define CONFIG_SIZE_OPTIMIZATIONS 1
#define CONFIG_COMPILER_COLOR_DIAGNOSTICS 1
#define CONFIG_COMPILER_OPT ""
#define CONFIG_RUNTIME_ERROR_CHECKS 1
#define CONFIG_KERNEL_BIN_NAME "zephyr"
#define CONFIG_OUTPUT_STAT 1
#define CONFIG_OUTPUT_DISASSEMBLY 1
#define CONFIG_OUTPUT_PRINT_MEMORY_USAGE 1
#define CONFIG_BUILD_OUTPUT_BIN 1
#define CONFIG_COMPAT_INCLUDES 1
