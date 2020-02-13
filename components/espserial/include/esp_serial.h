#ifndef ESP_SERIAL_H
#define ESP_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

// code in extern C block is the C++ code that will run in C code

#include "driver/gpio.h"
#include "sdkconfig.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "servo.h"

void rosserial_setup();   // setup rosserial
void rosserial_spinonce();  // this function will keep on running and check for new messages on subscribed topics

void rosserial_setup_rviz();
void rosserial_spinonce_rviz();

#ifdef __cplusplus
}
#endif

#endif /* ESP_SERIAL_H */
