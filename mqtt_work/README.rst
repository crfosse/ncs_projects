nRF9160: Modified simple MQTT
####################

This sample is a modified version of the nRF9160 mqtt_simple sample from the nRF Connect SDK. It simulates a common sensor application, with periodic uploads and occasional alarms.
A button press is used to simulate the alarm. Between uploads the modem is set to flight mode (AT+CFUN=4). 

MQTT subscribe functionaliyt is currently not tested/supported and is therefore commented out. 