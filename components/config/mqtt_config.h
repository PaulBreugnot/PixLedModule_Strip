#define MQTT_BROKER_IP CONFIG_MQTT_BROKER_IP
#define MQTT_BROKER_PORT CONFIG_MQTT_BROKER_PORT
#define MAIN_MQTT_EVENT_HANDLER main_mqtt_event_handler
#define TEST_MQTT_EVENT_HANDLER test_mqtt_event_handler

#include "mqtt_client.h"
#include "server_config.h"
#include "esp_log.h"
#include "esp_event_loop.h"

#define MQTT_TAG "MQTT"

#define MQTT_STATUS_WAITING -1
#define MQTT_STATUS_DISCONNECTED 0
#define MQTT_STATUS_CONNECTED 1

static char device_id[5];
static char client_id[10];
static char color_topic[50];
static char switch_topic[50];
static char const *connection_topic = "/connected";
static char const *disconnection_topic = "/disconnected";
static char const *check_topic = "/check";


struct mqtt_context {
  volatile int connected;
};

esp_err_t main_mqtt_event_handler(esp_mqtt_event_handle_t event);
esp_err_t test_mqtt_event_handler(esp_mqtt_event_handle_t event);

void save_mqtt_uri_to_nvs(const char* uri);
bool load_mqtt_uri_from_nvs(char** uri);
void mqtt_app_start(const char* uri, mqtt_event_callback_t mqtt_event_handler);
void clean_mqtt();
