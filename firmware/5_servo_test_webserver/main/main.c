#include "servo.h"
#include "freertos/task.h"

#include "sra_board.h"

#include <stdio.h>
#include <math.h>

#include "tuning_http_server.h"


#define TAG "MCPWM_SERVO_CONTROL"

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

static void mcpwm_servo_control(void *arg)
{
	enable_servo();

    while(1)
    {	

	set_angle_servo(&servo_a,(read_servo_const().servo_a));
	vTaskDelay(100);
	set_angle_servo(&servo_b,(read_servo_const().servo_b));
	vTaskDelay(100);
	set_angle_servo(&servo_c,(read_servo_const().servo_c));
	vTaskDelay(100);
          
    }
}

void app_main()
{
	ESP_LOGD(TAG,"Testing servo motors\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
	start_tuning_http_server();
}

