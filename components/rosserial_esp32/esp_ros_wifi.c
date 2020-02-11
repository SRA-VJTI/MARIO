/*
 * WiFi initialization for setting up ROS communication over TCP sockets
*/

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sdkconfig.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#define MAXIMUM_RETRY  5

#define ROS_SERVER_AP        CONFIG_ROSSERVER_AP
#define ROS_SERVER_PASS      CONFIG_ROSSERVER_PASS

static EventGroupHandle_t wifi_event_group;

const int IPV4_GOTIP_BIT = BIT0;

static const char *TAG = "esp-ros-wifi";

static int s_retry_num = 0;

static char addr_str[128];
static int addr_family;
static int ip_protocol;
static int sock;

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(wifi_event_group, IPV4_GOTIP_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        {
            if (s_retry_num < MAXIMUM_RETRY) {
                esp_wifi_connect();
                xEventGroupClearBits(wifi_event_group, IPV4_GOTIP_BIT);
                s_retry_num++;
                ESP_LOGI(TAG,"Retrying connection to AP");
            }
            ESP_LOGE(TAG,"Failed to connect to AP");
            break;
        }
    default:
        break;
    }
    return ESP_OK;
}

void esp_ros_wifi_init()
{
    nvs_flash_init();

    wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = ROS_SERVER_AP,
            .password = ROS_SERVER_PASS,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Waiting for AP connection...");
    xEventGroupWaitBits(wifi_event_group, IPV4_GOTIP_BIT, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");
}

void ros_tcp_connect(const char* host_ip, int port_num)
{
    struct sockaddr_in destAddr;
    destAddr.sin_addr.s_addr = inet_addr(host_ip);
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port_num);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);

    sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
    }

    /* Set sock to non-blocking mode (ASYNC)
     * "Lost sync with device, restarting.." error occurs if socket is blocking
     */
    fcntl(sock, F_SETFL, O_NONBLOCK);

    int err = connect(sock, (struct sockaddr *)&destAddr, sizeof(destAddr));
    if (err != 0 && errno != 119) {
        ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
    }
    ESP_LOGI(TAG, "Successfully connected");
}

void ros_tcp_send(uint8_t* data, int length)
{
    int err = send(sock, data, length, 0);
    if (err < 0) {
        ESP_LOGE(TAG, "Error occured during sending: errno %d", errno);
    }
}

int ros_tcp_read(uint8_t* buf, int length)
{
    int len = recv(sock, buf, length, 0);
    if (len < 0 && errno != 11) {
        ESP_LOGE(TAG, "Error receiving data: errno %d", errno);
        return -1;
    }
    return len;
}
