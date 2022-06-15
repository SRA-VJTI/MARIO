#include "servo.h"
#include "freertos/task.h"
#include "sra_board.h"

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

servo_config servo_d = {
	.servo_pin = SERVO_D,
	.min_pulse_width = CONFIG_SERVO_D_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_D_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_D_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_B,
};

int servo_A = 0, servo_B = 0, servo_C = 0, servo_D = 0;

static void mcpwm_servo_control(void *arg)
{
	enable_servo();
#ifdef CONFIG_ENABLE_OLED
	// Declaring the required OLED struct
	u8g2_t oled_config;

	// Initialising the OLED
	ESP_ERROR_CHECK(init_oled_mario(&oled_config));
#endif

	while (1)
	{
		set_angle_servo(&servo_a, servo_A);
		vTaskDelay(100);
		set_angle_servo(&servo_b, servo_B);
		vTaskDelay(100);
		set_angle_servo(&servo_c, servo_C);
		vTaskDelay(100);
		set_angle_servo(&servo_d, servo_D);
		vTaskDelay(100);
#ifdef CONFIG_ENABLE_OLED
		// Diplaying Servo A, Servo B, Servo C, Servo D values on OLED
		display_servo_values(servo_A, servo_B, servo_C, servo_D, &oled_config);
#endif
	}
}

void app_main()
{
	ESP_LOGD(TAG, "Testing servo motors\n");
	xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}
