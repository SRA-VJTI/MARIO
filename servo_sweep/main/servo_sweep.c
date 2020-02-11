#include "servo.h"

static void mcpwm_servo_control(void *arg)
{
    mcpwm_example_gpio_initialize();

    while(1)
    {	

    	for(int i = 0 ; i < 180 ; i++)
    	{
    		mcpwm_example_servo_control(i,i,i);
        	vTaskDelay(5);   
    	}
    	
    	for(int i = 180 ; i > 0; i--)
    	{
    		mcpwm_example_servo_control(i,i,i);
        	vTaskDelay(5);   
    	}
          
    }
}

void app_main()
{
    printf("Testing servo motor.......\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}
