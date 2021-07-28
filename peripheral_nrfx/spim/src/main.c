#include <assert.h>
#include <stdint.h>
#include <zephyr.h>
#include <nrfx_spim.h>

#define SCLK_PIN NRF_GPIO_PIN_MAP(0, 8)
#define MOSI_PIN NRF_GPIO_PIN_MAP(0, 9)
#define MISO_PIN NRF_GPIO_PIN_MAP(0,10)
#define CS_PIN   NRF_GPIO_PIN_MAP(0,11)

#define SPI_TRANSFER_SIZE 2

#define SPIM_INSTANCE 2

static const nrfx_spim_t spi = NRFX_SPIM_INSTANCE(SPIM_INSTANCE);
static uint8_t tx_buffer[SPI_TRANSFER_SIZE];
static const nrfx_spim_xfer_desc_t xfer = NRFX_SPIM_XFER_TX(tx_buffer, SPI_TRANSFER_SIZE);

void main(void)
{
    nrfx_err_t err_code;

    nrfx_spim_config_t spi_config = NRFX_SPIM_DEFAULT_CONFIG(SCLK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
    err_code = nrfx_spim_init(&spi, &spi_config, NULL, NULL);
    assert(err_code == NRFX_SUCCESS);

    printk("Value of NRF_SPIM2->PSEL.SCL : %d \n", NRF_SPIM2->PSEL.SCK);
	printk("Value of NRF_SPIM2->PSEL.MOSI : %d \n",NRF_SPIM2->PSEL.MOSI);
	printk("Value of NRF_SPIM2->PSEL.MISO : %d \n",NRF_SPIM2->PSEL.MISO);
	printk("Value of NRF_SPIM2->PSEL.CSN: %d \n",  NRF_SPIM2->PSEL.CSN);

    printk("Value of NRF_SPIM2_NS->PSEL.SCL : %d \n", NRF_SPIM2_NS->PSEL.SCK);
	printk("Value of NRF_SPIM2_NS->PSEL.MOSI : %d \n",NRF_SPIM2_NS->PSEL.MOSI);
	printk("Value of NRF_SPIM2_NS->PSEL.MISO : %d \n",NRF_SPIM2_NS->PSEL.MISO);
	printk("Value of NRF_SPIM2_NS->PSEL.CSN: %d \n",  NRF_SPIM2_NS->PSEL.CSN);


    while (1) {
        err_code = nrfx_spim_xfer(&spi, &xfer, NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER);
        assert(err_code == NRFX_SUCCESS);
        k_sleep(K_MSEC(1));
    }
}