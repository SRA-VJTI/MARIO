#include "ros.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/JointState.h"
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"

#define led_pin GPIO_NUM_2  // ledp pin for debugging

//////////////////////////////////////////////////////////////////////////////
void messageCb(const geometry_msgs::Vector3 &msg);
void messageCb_rviz(const sensor_msgs::JointState &msg);
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Vector3> arm("ros_arm_control", &messageCb);
ros::Subscriber<sensor_msgs::JointState> arm_rviz("joint_states", &messageCb_rviz);
//////////////////////////////////////////////////////////////////////////////

void blinkDebugLed()
{
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);

    gpio_set_level(led_pin, 1);
    vTaskDelay(50);

    gpio_set_level(led_pin, 0);
    vTaskDelay(50);
}

void messageCb(const geometry_msgs::Vector3 &msg)
{
    ESP_LOGD("info", "%s", "new message from publisher");

    blinkDebugLed();

    ESP_LOGD("angle 0", "%f", msg.x);
    ESP_LOGD("angle 1", "%f", msg.y);
    ESP_LOGD("angle 2", "%f", msg.z);

    mcpwm_example_servo_control(msg.x, msg.y, msg.z);
}

void rosserial_setup()
{
    nh.initNode();                  // Initialize ROS
    nh.subscribe(arm);              // subscribe to topic
}

void rosserial_spinonce()
{
    nh.spinOnce();
}

void messageCb_rviz(const sensor_msgs::JointState &msg)
{
    ESP_LOGD("info", "%s", "new message from publisher");

    // add some kind of indication outside like turn on led

    ESP_LOGD("timestamp", "%d", msg.header.seq);
    ESP_LOGD("angle 0", "%f", msg.position[0]);
    ESP_LOGD("angle 1", "%f", msg.position[1]);
    ESP_LOGD("angle 2", "%f", msg.position[2]);

    mcpwm_example_servo_control(msg.position[0], msg.position[1], msg.position[2]);
}

void rosserial_setup_rviz()
{
    ESP_LOGD("init moveit", "%f", 20.0);
    nh.initNode();                  // Initialize ROS
    nh.subscribe(arm_rviz);              // subscribe to topic
    ESP_LOGD("init moveit", "%f", 23.0);
}

void rosserial_spinonce_rviz()
{
    nh.spinOnce();
}
