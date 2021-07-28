#include <zephyr.h>
#include <sys/printk.h>
#include "nrfx_spis.h"

#define PIN_SCK 29
#define PIN_MOSI 31
#define PIN_MISO 30
#define PIN_CSN 28
#define SPIS_NR 0


#include <devicetree.h>
#include <drivers/gpio.h>
#define LED0_NODE DT_ALIAS(led2)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
//#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define PIN	3
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
const struct device *led;

nrfx_spis_t spis_t = NRFX_SPIS_INSTANCE(SPIS_NR);
nrfx_spis_config_t spis_config_t = NRFX_SPIS_DEFAULT_CONFIG(PIN_SCK,PIN_MOSI,PIN_MISO,PIN_CSN);

uint8_t readend=0;

K_SEM_DEFINE(SPI_EVENT, 0, 1);

uint8_t rx_buffer[8];
uint8_t tx_buffer[8];
uint8_t tmpbuffer[8] = {0};
void spis_event_handler_t(nrfx_spis_evt_t const *p_event, void *p_context){
    //printk("received\n");
    int err;

    switch(p_event->evt_type){
        case NRFX_SPIS_XFER_DONE:
		if(rx_buffer[0]!= 255)
		{	
			printk("read");
			for(int i=0;i<8;i++){
				printk("%d ",rx_buffer[i]);
			}
			printk("\r\n");	
			
		}
            err = nrfx_spis_buffers_set(&spis_t, tx_buffer, sizeof(tx_buffer), rx_buffer, sizeof(rx_buffer));
            if(err != NRFX_SUCCESS){
                printk("Error with setting.\n");
            }
		k_sem_give(&SPI_EVENT);

            break;

        default:
            ;
    }
	
}

void init_spis(){
    int err;
    err = nrfx_spis_init(&spis_t,&spis_config_t,spis_event_handler_t,NULL);
    if(err != NRFX_SUCCESS){
        printk("Error with init.\n");
    } else {
        printk("SPIS started.\n");
    }
}

void main(void)
{
    int err,k=0,ret;
    init_spis();

    bool low = true;
    bool high =! low;
	led = device_get_binding(LED0);
	if (led == NULL) {
		return;
	}

	ret = gpio_pin_configure(led, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}
        gpio_pin_set(led, PIN, (int)low);

    err = nrfx_spis_buffers_set(&spis_t, tx_buffer, sizeof(tx_buffer), rx_buffer, sizeof(rx_buffer));
    if(err != NRFX_SUCCESS){
        printk("Error with setting.\n");
    }
	

	while(true){

		if(k_sem_take(&SPI_EVENT, K_FOREVER)==0){
			gpio_pin_set(led, PIN, (int)low);

			printk("write ");
			for(int i = 0 ; i< 8 ; i++)
				tx_buffer[i] = k+i;
			k++;
			
			for(int i = 0 ; i< 8 ; i++)
				printk("%d ",tx_buffer[i]);
			printk("\r\n");

			gpio_pin_set(led, PIN, (int)high);	
			gpio_pin_set(led, PIN, (int)low);
	
		}

	}

}