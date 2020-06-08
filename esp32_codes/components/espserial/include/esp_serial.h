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
#include "logger.h"

#define led_pin GPIO_NUM_2  // led pin for debugging

void rosserial_setup();          // setup rosserial
void rosserial_spinonce();       // this function will keep on running and check for new messages on subscribed topics

void rosserial_setup_rviz();     // setup rosserial for rviz
void rosserial_spinonce_rviz();  // this function will keep on running and check for new messages on subscribed topics

#ifdef __cplusplus
}
#endif
#endif
