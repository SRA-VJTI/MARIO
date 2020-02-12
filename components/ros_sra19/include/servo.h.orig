
/*

Copyright (c) 2019, Society of Robotics and Automation, VJTI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef SERVO_H
#define SERVO_h

#include <string.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

//You can get these value from the datasheet of servo you use

#define MICRO_SERVO_MIN_PULSEWIDTH 800 //Minimum pulse width in microsecond for micro servo
#define MICRO_SERVO_MAX_PULSEWIDTH 2000 //Maximum pulse width in microsecond for micro servo

#define SERVO_MIN_PULSEWIDTH 500 //Minimum pulse width in microsecond for servo
#define SERVO_MAX_PULSEWIDTH 3000 //Maximum pulse width in microsecond for SERVO_MAX_DEGREE

#define SERVO_MAX_DEGREE 180

#define SERVO_PIN_1 18
#define SERVO_PIN_2 19
#define SERVO_PIN_3 21



int theta1,theta2,theta3;
int PWM1 ,PWM2 ,PWM3;


void mcpwm_example_gpio_initialize();

uint32_t micro_servo_per_degree_init(uint32_t degree_of_rotation);

uint32_t servo_per_degree_init(uint32_t degree_of_rotation);

void mcpwm_example_servo_control(int theta1,int theta2,int theta3);

#endif
