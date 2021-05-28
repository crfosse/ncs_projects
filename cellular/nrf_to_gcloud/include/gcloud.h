#ifndef __MQTT_H__
#define __MQTT_H__

#include <net/mqtt.h>

#define strlens(s) (s==NULL?0:strlen(s))

typedef void (*received_config_handler_t)(const struct mqtt_publish_message *message);

/**
 * @brief Publishes data to Google Cloud.
 * 
 * @param[in] data A pointer to the data to be sent.
 * @param[in] size The size of the data to be sent.
 * @param[in] qos The Quality of Serive level to be used when sending the telemetry.
 * 
 * @note Google Cloud does only support QoS 0 and QoS 1, not QoS 2
 * 
 * @retval 0 or an error code indicating reason for failure.
 */
// CANDO: Make it possible to publish gps to subtopics
int gcloud_publish(uint8_t *data, uint32_t size, enum mqtt_qos qos);

/**
 * @brief Publishes device state to Google Cloud.
 * 
 * @param[in] data A pointer to the data to be sent.
 * @param[in] size The size of the data to be sent.
 * @param[in] qos The Quality of service level to be used when sending the state.
 * 
 * @note Google Cloud does only support QoS 0 and QoS 1, not Qos 2.
 * @note Google Cloud limits state updates to 1 update per second, per device. 
 *       However, for best results, device state should be updated much less often 
 *       - at most, once every 10 second.
 * 
 * @retval 0 or an error code indicating reson for failure.
 */
int gcloud_publish_state(uint8_t *data, uint32_t size, enum mqtt_qos qos);

/**
 * @brief Connects the device to Google Cloud, and subscribes to Google Cloud's configuration topic.
 * 
 * @note gcloud_provision must be called before this.
 * @note Shall be called before trying to send data to Google Cloud.
 * @note The modem must be turned on, and connected before this function can be called.
 * 
 * @param[in] received_config_cb Callback function which will be called when a configuration 
 *            update is received from Google Cloud.
 * 
 * @retval - or an error code indicating reason for failure.
 */
// CANDO: make it possible to set keep-alive checks, and input check intervals
// CANDO: make it possible to decide what QoS level the subscription to config should be
int gcloud_connect(received_config_handler_t received_config_cb);

/**
 * @brief Initializes the module and provisions the modem so that an TLS 
 * connection can be established to Google Cloud.
 * 
 * @note Shall be called before the modem is turned on.
 * @note Shall be called before gcloud_connect.
 * @note If module initialization fails, no module APIs shall be called.
 * 
 * @retval 0 or an error code indicating reason for failure.
 */
int gcloud_provision(void);

/**
 * @brief Disconnects the device from Google Cloud.
 * 
 * @retval 0 or an error code indicating reason for failure.
 */
int gcloud_disconnect(void);

/**
 * @brief Google Cloud Thread entry.
 */
extern void gcloud_thread(void *unused1, void *unused2, void *unused3);

#endif /* __MQTT_H__ */