#include <device.h>
#include <toolchain.h>

/* 1 : /soc/peripheral@40000000/clock@5000:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/peripheral@40000000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_clock_5000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 2 : /soc/peripheral@40000000/uart@9000:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/peripheral@40000000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_uart_9000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 3 : /soc/peripheral@40000000/uart@8000:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/peripheral@40000000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_uart_8000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 4 : /soc/cryptocell-sw:
 * - (/soc)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_cryptocell_sw[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 5 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sys_init_sys_clock_driver_init0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 6 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_nrf91_socket[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 7 : /soc/peripheral@40000000/gpio@842500:
 * - (/soc/peripheral@40000000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_gpio_842500[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 8 : /soc/peripheral@40000000/uart@9000/nrf-sw-lpuart:
 * - /soc/peripheral@40000000/uart@9000
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_uart_9000_S_nrf_sw_lpuart[] = { 2, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 9 : /soc/peripheral@40000000/i2c@a000:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/peripheral@40000000)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_i2c_a000[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 10 : /soc/peripheral@40000000/spi@b000:
 * - (/soc/interrupt-controller@e000e100)
 * - (/soc/peripheral@40000000)
 * - /soc/peripheral@40000000/gpio@842500
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_soc_S_peripheral_40000000_S_spi_b000[] = { 7, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };
