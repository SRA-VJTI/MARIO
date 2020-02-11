#include "ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

#define led_pin GPIO_NUM_2  // ledp pin for debugging

ros::NodeHandle nh;

// using vector3
struct angles{
  int theta[3];
};

angles parseData(const char* data){

    char theta[3][20];
    int counter_1 = 0;
    int counter_2 = 0;
    angles ret;

    for(int i=0; i < strlen(data); i++)
    {
      if(data[i] == ' ')
      {
        theta[counter_1][counter_2+1] = '\0';
        counter_1++;
        counter_2 = 0;
      }
      else
      {
        theta[counter_1][counter_2] = data[i];
        counter_2++;
      }
    }

    ret.theta[0] = atoi(theta[0]);
    ret.theta[1] = atoi(theta[1]);
    ret.theta[2] = atoi(theta[2]);

    return ret;
}

void blinkDebugLed(){

  gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
  
  gpio_set_level(led_pin, 1);
  vTaskDelay(50);
  
  gpio_set_level(led_pin, 0);
  vTaskDelay(50);
}

void messageCb(const std_msgs::String& msg){    

    ESP_LOGD("info", "%s", "new message from publisher");

    blinkDebugLed();

    angles servoAngles = parseData(msg.data);

    ESP_LOGD("angle 0", "%d", servoAngles.theta[0]);
    ESP_LOGD("angle 1", "%d", servoAngles.theta[1]);
    ESP_LOGD("angle 2", "%d", servoAngles.theta[2]);

    mcpwm_example_servo_control(servoAngles.theta[0], servoAngles.theta[1], servoAngles.theta[2]);    
}

ros::Subscriber<std_msgs::String> arm("ros_arm_control", &messageCb);

void rosserial_setup()
{
  nh.initNode();                   // Initialize ROS
  nh.subscribe(arm);              // subscribe to topic
}

void rosserial_spinonce()
{
  nh.spinOnce();
}