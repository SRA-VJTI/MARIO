#include "servo.h"

static void mcpwm_servo_control(void *arg)
{
    mcpwm_example_gpio_initialize();
    while(1)
    {   
        mcpwm_example_servo_control(0,0,0);
          
    }
}

void app_main()
{
    printf("Testing servo motor.......\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}
