#include "ros.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/JointState.h"
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"

//////////////////////////////////////////////////////////////////////////////
static const char* TAG_C = "ros_control";
static const char* TAG_RVIZ = "ros_control_rviz";
void message_callback(const geometry_msgs::Vector3 &msg);
void message_callback_rviz(const sensor_msgs::JointState &msg);
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Vector3> arm("ros_arm_control", &message_callback);
ros::Subscriber<sensor_msgs::JointState> arm_rviz("joint_states", &message_callback_rviz);
//////////////////////////////////////////////////////////////////////////////

void debug_blink_led()
{
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);

    gpio_set_level(led_pin, 1);
    vTaskDelay(50);

    gpio_set_level(led_pin, 0);
    vTaskDelay(50);
}

void message_callback(const geometry_msgs::Vector3 &msg)
{
    logD(TAG_C, "%s", "new message from publisher");

    debug_blink_led();

    logD(TAG_C, "angle [BASE]:     %f", msg.x);
    logD(TAG_C, "angle [SHOUDLER]: %f", msg.y);
    logD(TAG_C, "angle [ELBOW]:    %f", msg.z);

    servo_control(msg.x, msg.y, msg.z);
}

void rosserial_setup()
{
    logD(TAG_C, "%s", "ros controlled arm through custom publisher\n\n");
    
    nh.initNode();                  // Initialize ROS
    nh.subscribe(arm);              // subscribe to topic
}

void rosserial_spinonce()
{
    nh.spinOnce();
}

void message_callback_rviz(const sensor_msgs::JointState &msg)
{
    logD(TAG_RVIZ, "%s", "new message from publisher");

    logD(TAG_RVIZ, "timestamp:        %d", msg.header.seq);
    logD(TAG_RVIZ, "angle [BASE}:     %f", msg.position[0]);
    logD(TAG_RVIZ, "angle [SHOUDLER]: %f", msg.position[1]);
    logD(TAG_RVIZ, "angle [ELBOW]:    %f", msg.position[2]);

    servo_control(msg.position[0], msg.position[1], msg.position[2]);
}

void rosserial_setup_rviz()
{
    logD(TAG_RVIZ, "%s", "ros controlled arm through rviz\n\n");
    
    nh.initNode();
    nh.subscribe(arm_rviz);
}

void rosserial_spinonce_rviz()
{
    nh.spinOnce();
}
