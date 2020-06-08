#include "servo.h"

static void mcpwm_servo_control(void *arg)
{
    servo_gpio_initialize();
    while(1)
    {   
        servo_control(0,0,0);
          
    }
}

void app_main()
{
    logD("servo_control", "%s", "setting servo motors to zero\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_example_servo_control", 4096, NULL, 5, NULL);
}
