// Including necessary libraries for Rosserial
#include "ros.h"
#include "std_msgs/Float64.h"

// Including necessary ESP-IDF libraries
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"


#define TAG_C "ROSSERIAL_GAZEBO"
#define pi 3.141592653589


// callback functions called when publisher publishes the message
void message_callback1(const std_msgs::Float64 &msg);
void message_callback2(const std_msgs::Float64 &msg);
void message_callback3(const std_msgs::Float64 &msg);

// Subscriber to the joint controller messages
ros::Subscriber<std_msgs::Float64> arm1("/manipulator/joint_1_controller/command", &message_callback1);
ros::Subscriber<std_msgs::Float64> arm2("/manipulator/joint_2_controller/command", &message_callback2);
ros::Subscriber<std_msgs::Float64> arm3("/manipulator/joint_3_controller/command", &message_callback3);

// Node handler to access nodes
ros::NodeHandle nh;

// configuration for Servo A
static servo_config servo_a = {
	.servo_pin = SERVO_A,
	.min_pulse_width = CONFIG_SERVO_A_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_A_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_A_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_A,
};

// configuration for Servo B
static servo_config servo_b = {
	.servo_pin = SERVO_B,
	.min_pulse_width = CONFIG_SERVO_B_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_B_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_B_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_B,
};

// configuration for Servo C
static servo_config servo_c = {
	.servo_pin = SERVO_C,
	.min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_C_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_A,
};


void rosserial_setup()
{
    ESP_LOGD(TAG_C, "%s", "ROS contolled arm th\n\n");
    
    nh.initNode();                  // Initialize ROS
    nh.subscribe(arm1);             // subscribe to topic
    nh.subscribe(arm2); 
    nh.subscribe(arm3); 
}

// this function will keep on running and check for new messages on subscribed topics
void rosserial_spinonce()
{
    nh.spinOnce();
}

void message_callback1(const std_msgs::Float64 &msg)
{

    ESP_LOGD(TAG_C, "angle [BASE]:     %f", msg.data);
    set_angle_servo(&servo_c,msg.data*(180/pi));
}

void message_callback2(const std_msgs::Float64 &msg)
{

    ESP_LOGD(TAG_C, "angle [SHOUDLER]: %f", msg.data);
    set_angle_servo(&servo_b,msg.data *(180/pi));
}

void message_callback3(const std_msgs::Float64 &msg)
{

    ESP_LOGD(TAG_C, "angle [ELBOW]:    %f", msg.data);
    set_angle_servo(&servo_a,msg.data*(180/pi));
}



