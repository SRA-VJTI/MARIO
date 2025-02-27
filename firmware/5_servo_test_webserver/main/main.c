/*
MIT License

Copyright (c) 2024 Society of Robotics and Automation

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
#include "sra_board.h"
#include <stdio.h>
#include <math.h>
#include "tuning_http_server.h"

#define TAG "MCPWM_SERVO_CONTROL"
#define SMOOTHING_STEPS 20
#define SMOOTHING_DELAY 20

typedef struct {
    float current_a;
    float current_b;
    float current_c;
    float current_d;
} servo_positions;

static servo_positions current_pos = {0, 0, 0, 0};

servo_config servo_a = {
    .servo_pin = SERVO_A,
    .min_pulse_width = CONFIG_SERVO_A_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_A_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_A_MAX_DEGREE,
    .mcpwm_num = MCPWM_UNIT_0,
    .timer_num = MCPWM_TIMER_0,
    .gen = MCPWM_OPR_A,
};

servo_config servo_b = {
    .servo_pin = SERVO_B,
    .min_pulse_width = CONFIG_SERVO_B_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_B_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_B_MAX_DEGREE,
    .mcpwm_num = MCPWM_UNIT_0,
    .timer_num = MCPWM_TIMER_0,
    .gen = MCPWM_OPR_B,
};

servo_config servo_c = {
    .servo_pin = SERVO_C,
    .min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_C_MAX_DEGREE,
    .mcpwm_num = MCPWM_UNIT_0,
    .timer_num = MCPWM_TIMER_1,
    .gen = MCPWM_OPR_A,
};

servo_config servo_d = {
    .servo_pin = SERVO_D,
    .min_pulse_width = CONFIG_SERVO_D_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_D_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_D_MAX_DEGREE,
    .mcpwm_num = MCPWM_UNIT_0,
    .timer_num = MCPWM_TIMER_1,
    .gen = MCPWM_OPR_B,
};

void smooth_servo_motion(servo_config *servo, float current_angle, float target_angle) {
    float angle_diff = target_angle - current_angle;
    float step = angle_diff / SMOOTHING_STEPS;

    for(int i = 0; i < SMOOTHING_STEPS; i++) {
        float intermediate_angle = current_angle + (step * (i + 1));
        set_angle_servo(servo, intermediate_angle);
        vTaskDelay(pdMS_TO_TICKS(SMOOTHING_DELAY));
    }
}

#ifdef CONFIG_ENABLE_OLED

void update_oled()
{
    // Displaying Servo A, Servo B, Servo C, Servo D values on OLED
    while (1)
    {
        display_servo_values(read_servo(&servo_a), read_servo(&servo_b),
                           read_servo(&servo_c), read_servo(&servo_d));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

#endif

static void mcpwm_servo_control(void *arg)
{
    enable_servo();

    // Initialize current positions
    current_pos.current_a = read_servo(&servo_a);
    current_pos.current_b = read_servo(&servo_b);
    current_pos.current_c = read_servo(&servo_c);
    current_pos.current_d = read_servo(&servo_d);

    while (1)
    {
        // Get target values from web server
        float target_a = read_servo_const().servo_a;
        float target_b = read_servo_const().servo_b;
        float target_c = read_servo_const().servo_c;
        float target_d = read_servo_const().servo_d;

        // Smooth motion for each servo
        if (fabs(target_a - current_pos.current_a) > 0.5) {
            smooth_servo_motion(&servo_a, current_pos.current_a, target_a);
            current_pos.current_a = target_a;
        }

        if (fabs(target_b - current_pos.current_b) > 0.5) {
            smooth_servo_motion(&servo_b, current_pos.current_b, target_b);
            current_pos.current_b = target_b;
        }

        if (fabs(target_c - current_pos.current_c) > 0.5) {
            smooth_servo_motion(&servo_c, current_pos.current_c, target_c);
            current_pos.current_c = target_c;
        }

        if (fabs(target_d - current_pos.current_d) > 0.5) {
            smooth_servo_motion(&servo_d, current_pos.current_d, target_d);
            current_pos.current_d = target_d;
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main()
{
    ESP_LOGD(TAG, "Testing servo motors\n");

#ifdef CONFIG_ENABLE_OLED
    ESP_ERROR_CHECK(init_oled());
    display_logo(MARIO_LOGO);
    vTaskDelay(pdMS_TO_TICKS(100));
    xTaskCreatePinnedToCore(update_oled, "update oled", 4096, NULL, 5, NULL, 0);
#endif

    xTaskCreatePinnedToCore(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL, 1);
    start_tuning_http_server();
}
