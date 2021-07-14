#include "servo.h"
#include "freertos/task.h"

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
    	for(int i = 0 ; i < 180 ; i++)
    	{
			set_angle_servo(&servo_a, i);
			set_angle_servo(&servo_b, i);
			set_angle_servo(&servo_c, i);
        	vTaskDelay(5);   
    	}
    	
    	for(int i = 180 ; i > 0; i--)
    	{
			set_angle_servo(&servo_a, i);
			set_angle_servo(&servo_b, i);
			set_angle_servo(&servo_c, i);
        	vTaskDelay(5);    
    	}
          
    }
}

void app_main()
{
	ESP_LOGD(TAG,"Testing servo motors\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}

