#ifndef ESP_SERIAL_H
#define ESP_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/gpio.h"
#include "sdkconfig.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "servo.h"

void rosserial_setup();     // setup rosserial for rviz
void rosserial_spinonce();  // this function will keep on running and check for new messages on subscribed topics

#ifdef __cplusplus
}
#endif
#endif