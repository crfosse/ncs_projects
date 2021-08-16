/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/**@file
 *@brief AWS IoT library header.
 */

#ifndef AWS_IOT_H__
#define AWS_IOT_H__

#include <stdio.h>
#include <net/mqtt.h>

/**
 * @defgroup aws_iot AWS IoT library
 * @{
 * @brief Library to connect the device to the GCloud IoT Core message broker.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief AWS IoT shadow topics, used in messages to specify which shadow
 *         topic that will be published to.
 */
enum gcloud_topic_type {
	/** Unknown device shadow topic. */
	GCLOUD_TOPIC_UNKNOWN = 0x0,
	/** This topic type corresponds to
	 *  $aws/things/<thing-name>/shadow/get, publishing an empty message
	 *  to this topic requests the device shadow document.
	 */
	GCLOUD_TOPIC_GET,
	/** This topic type corresponds to
	 *  $aws/things/<thing-name>/shadow/update, publishing data to this
	 *  topic updates the device shadow document.
	 */
	GCLOUD_TOPIC_UPDATE,
	/** This topic type corresponds to
	 *  $aws/things/<thing-name>/shadow/delete, publishing an empty message
	 *  to this topic deletes the device Shadow document.
	 */
	GCLOUD_TOPIC_DELETE
};

/**@ AWS broker disconnect results. */
enum gcloud_disconnect_result {
	GCLOUD_DISCONNECT_USER_REQUEST,
	GCLOUD_DISCONNECT_CLOSED_BY_REMOTE,
	GCLOUD_DISCONNECT_INVALID_REQUEST,
	GCLOUD_DISCONNECT_MISC,
	GCLOUD_DISCONNECT_COUNT
};

/**@brief AWS broker connect results. */
enum gcloud_connect_result {
	GCLOUD_CONNECT_RES_SUCCESS = 0,
	GCLOUD_CONNECT_RES_ERR_NOT_INITD = -1,
	GCLOUD_CONNECT_RES_ERR_INVALID_PARAM = -2,
	GCLOUD_CONNECT_RES_ERR_NETWORK = -3,
	GCLOUD_CONNECT_RES_ERR_BACKEND = -4,
	GCLOUD_CONNECT_RES_ERR_MISC = -5,
	GCLOUD_CONNECT_RES_ERR_NO_MEM = -6,
	/* Invalid private key */
	GCLOUD_CONNECT_RES_ERR_PRV_KEY = -7,
	/* Invalid CA or client cert */
	GCLOUD_CONNECT_RES_ERR_CERT = -8,
	/* Other cert issue */
	GCLOUD_CONNECT_RES_ERR_CERT_MISC = -9,
	/* Timeout, SIM card may be out of data */
	GCLOUD_CONNECT_RES_ERR_TIMEOUT_NO_DATA = -10,
	GCLOUD_CONNECT_RES_ERR_ALREADY_CONNECTED = -11,
};

/** @brief AWS IoT notification event types, used to signal the application. */
enum gcloud_evt_type {
	/** Connecting to AWS IoT broker. */
	GCLOUD_EVT_CONNECTING = 0x1,
	/** Connected to AWS IoT broker. */
	GCLOUD_EVT_CONNECTED,
	/** AWS IoT library has subscribed to all configured topics. */
	GCLOUD_EVT_READY,
	/** Disconnected to AWS IoT broker. */
	GCLOUD_EVT_DISCONNECTED,
	/** Data received from AWS message broker. */
	GCLOUD_EVT_DATA_RECEIVED,
	/** AWS IoT library irrecoverable error. */
	GCLOUD_EVT_ERROR
};

/** @brief AWS IoT topic data. */
struct gcloud_topic_data {
	/** Type of shadow topic that will be published to. */
	enum gcloud_topic_type type;
	/** Pointer to string of application specific topic. */
	const char *str;
	/** Length of application specific topic. */
	size_t len;
};

/** @brief Structure used to declare a list of application specific topics
 *         passed in by the application.
 */
struct gcloud_app_topic_data {
	/** List of application specific topics. */
	struct mqtt_topic list[CONFIG_AWS_IOT_APP_SUBSCRIPTION_LIST_COUNT];
	/** Number of entries in topic list. */
	size_t list_count;
};

/** @brief AWS IoT transmission data. */
struct gcloud_data {
	/** Topic data is sent/received on. */
	struct gcloud_topic_data topic;
	/** Pointer to data sent/received from the AWS IoT broker. */
	char *ptr;
	/** Length of data. */
	size_t len;
	/** Quality of Service of the message. */
	enum mqtt_qos qos;
};

/** @brief Struct with data received from AWS IoT broker. */
struct gcloud_evt {
	/** Type of event. */
	enum gcloud_evt_type type;
	union {
		struct aws_iot_data msg;
		int err;
		bool persistent_session;
	} data;
};

/** @brief AWS IoT library asynchronous event handler.
 *
 *  @param[in] evt The event and any associated parameters.
 */
typedef void (*gcloud_evt_handler_t)(const struct gcloud_evt *evt);

/** @brief Structure for AWS IoT broker connection parameters. */
struct gcloud_config {
	/** Socket for AWS IoT broker connection */
	int socket;
	/** Client id for AWS IoT broker connection, used when
	 *  @option{CONFIG_AWS_IOT_CLIENT_ID_APP} is set. If not set an internal
	 *  configurable static client id is used.
	 */
	char *client_id;
	/** Length of client_id string. */
	size_t client_id_len;
};

/** @brief Initialize the module.
 *
 *  @warning This API must be called exactly once, and it must return
 *           successfully.
 *
 *  @param[in] config Pointer to struct containing connection parameters.
 *  @param[in] event_handler Pointer to event handler to receive AWS IoT module
 *                           events.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_init(const struct aws_iot_config *const config,
		 aws_iot_evt_handler_t event_handler);

/** @brief Connect to the AWS IoT broker.
 *
 *  @details This function exposes the MQTT socket to main so that it can be
 *           polled on.
 *
 *  @param[out] config Pointer to struct containing connection parameters,
 *                     the MQTT connection socket number will be copied to the
 *                     socket entry of the struct.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_connect(struct aws_iot_config *const config);

/** @brief Disconnect from the AWS IoT broker.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_disconnect(void);

/** @brief Send data to AWS IoT broker.
 *
 *  @param[in] tx_data Pointer to struct containing data to be transmitted to
 *                     the AWS IoT broker.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_send(const struct aws_iot_data *const tx_data);

/** @brief Get data from AWS IoT broker
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_input(void);

/** @brief Ping AWS IoT broker. Must be called periodically
 *         to keep connection to broker alive.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_ping(void);

/** @brief Add a list of application specific topics that will be subscribed to
 *         upon connection to AWS IoT broker.
 *
 *  @param[in] topic_list Pointer to list of topics.
 *  @param[in] list_count Number of entries in the list.
 *
 *  @return 0 If successful.
 *            Otherwise, a (negative) error code is returned.
 */
int gcloud_subscription_topics_add(
			const struct aws_iot_topic_data *const topic_list,
			size_t list_count);

#ifdef __cplusplus
}
#endif

/**
 *@}
 */

#endif /* AWS_IOT_H__ */
