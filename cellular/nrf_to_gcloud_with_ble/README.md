# nRF9160: Google Cloud IoT Core with BLE
####################

This project enables the nRF9160DK and Thingy:91 to connect to the Google Cloud IoT Core using MQTT, as well as implementing BLE functionality. Follow the instructions to setup the application correctly.

## BLE support on Thingy:91
There isn't native support for BLE on the Thingy:91 in NCS yet, but [this fork](https://github.com/crfosse/sdk-nrf/tree/bee_dev_new) implements the necessary changes to the Thingy:91 board files. Change to this fork when building this sample, and the hci_lpuart sample for the Thingy:91.
