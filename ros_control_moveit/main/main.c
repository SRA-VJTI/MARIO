#include "stdio.h"
#include "esp_serial.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    servo_gpio_initialize();  // init gpio pwm
    rosserial_setup_rviz(); // run rosserial setup

    while (1)
    {
        rosserial_spinonce_rviz();
        vTaskDelay(100);
    }
}