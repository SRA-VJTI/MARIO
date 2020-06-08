#include "stdio.h"
#include "esp_serial.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    servo_gpio_initialize();  // init gpio pwm
    rosserial_setup();        // run rosserial setup

    while (1)
    {
        rosserial_spinonce();
        vTaskDelay(100);
    }
}