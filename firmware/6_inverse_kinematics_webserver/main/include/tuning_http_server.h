#ifndef TUNING_HTTP_SERVER_H
#define TUNING_HTTP_SERVER_H

#include <string.h>
#include <fcntl.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mdns.h"
#include "lwip/apps/netbiosns.h"
#include "esp_http_server.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "cJSON.h"
#include "sdkconfig.h"
#include "wifi_handler.h"

#define MDNS_INSTANCE "MARIO servo testing web server"
#define MDNS_HOST_NAME CONFIG_MDNS_HOST_NAME
#define WEB_MOUNT_POINT "/www"
#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
#define SCRATCH_BUFSIZE (10240)
#define CHECK_FILE_EXTENSION(filename, ext) (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

// Structure to store the Base,Shoulder,Elbow angles
typedef struct pid_const
{
    double servo_a; // Elbow Angle
    double servo_b; // Shoulder Angle
    double servo_c; // Base Angle
} servo_const_t;

//  Returns the feasible angles from all the possible Joint angles 
servo_const_t computeAngles(double*);

// Returns the three servo angles
servo_const_t read_servo_const();


void start_tuning_http_server();

#endif