#include "servo.h"

static void mcpwm_servo_control(void *arg)
{
    servo_gpio_initialize();

    while(1)
    {	
    	for(int i = 0 ; i < 180 ; i++)
    	{
    		servo_control_sweep(i,i,i);
        	vTaskDelay(5);   
    	}
    	
    	for(int i = 180 ; i > 0; i--)
    	{
    		servo_control_sweep(i,i,i);
        	vTaskDelay(5);   
    	}
          
    }
}

void app_main()
{
	logD("servo_control", "%s", "testing servo motors\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}
