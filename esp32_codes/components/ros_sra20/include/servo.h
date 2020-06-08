/*
Copyright (c) 2020, Society of Robotics and Automation, VJTI

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
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "esp_attr.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "logger.h"

#define MICRO_SERVO_MIN_PULSEWIDTH CONFIG_MICRO_SERVO_MIN_PULSEWIDTH
#define MICRO_SERVO_MAX_PULSEWIDTH CONFIG_MICRO_SERVO_MAX_PULSEWIDTH

#define SERVO_MIN_PULSEWIDTH CONFIG_SERVO_MIN_PULSEWIDTH
#define SERVO_MAX_PULSEWIDTH CONFIG_SERVO_MAX_PULSEWIDTH
#define SERVO_MAX_DEGREE CONFIG_SERVO_MAX_DEGREE

#define SERVO_BASE CONFIG_SERVO_BASE
#define SERVO_SHOULDER CONFIG_SERVO_SHOULDER
#define SERVO_ELBOW CONFIG_SERVO_ELBOW

int theta1, theta2, theta3;
int PWM1 , PWM2 , PWM3;

void servo_gpio_initialize();
uint32_t micro_servo_per_degree_init(uint32_t degree_of_rotation);
uint32_t servo_per_degree_init(uint32_t degree_of_rotation);
void servo_control(int theta1, int theta2, int theta3);
void servo_control_sweep(int theta1, int theta2, int theta3);

#endif
