#include <assert.h>
#include <stdint.h>
#include <zephyr.h>
#include <nrfx_spim.h>

#define SCLK_PIN NRF_GPIO_PIN_MAP(0, 8)
#define MOSI_PIN NRF_GPIO_PIN_MAP(0, 9)
#define MISO_PIN NRF_GPIO_PIN_MAP(0,10)
#define CS_PIN   NRF_GPIO_PIN_MAP(0,11)

#define SPI_TRANSFER_SIZE 2

static const nrfx_spim_t spi = NRFX_SPIM_INSTANCE(1);
static uint8_t tx_buffer[SPI_TRANSFER_SIZE];
static const nrfx_spim_xfer_desc_t xfer = NRFX_SPIM_XFER_TX(tx_buffer, SPI_TRANSFER_SIZE);

void main(void)
{
	printk("Starting SPIM sample\n");

    nrfx_err_t err_code;

    nrfx_spim_config_t spi_config = NRFX_SPIM_DEFAULT_CONFIG(SCLK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

	printk("SPIM init\n");
    err_code = nrfx_spim_init(&spi, &spi_config, NULL, NULL);
	printk("SPIM error: %d\n",err_code);
    assert(err_code == NRFX_SUCCESS);

    printk("Value of SPIM->MOSI : %d \n",NRF_SPIM1->PSEL.MOSI);
	printk("Value of SPIM->MISO: %d \n",NRF_SPIM1->PSEL.MISO);
	printk("Value of SPIM->CSN: %d \n",NRF_SPIM1->PSEL.CSN);
	printk("Value of SPIM->SCK: %d \n",NRF_SPIM1->PSEL.SCK);
    while (1) {
        err_code = nrfx_spim_xfer(&spi, &xfer, NRFX_SPIM_FLAG_NO_XFER_EVT_HANDLER);
        assert(err_code == NRFX_SUCCESS);
        k_sleep(K_MSEC(1));
    }
}