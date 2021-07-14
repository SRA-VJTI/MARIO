// Including necessary libraries for Rosserial
#include "ros.h"
#include "sensor_msgs/JointState.h"

// Including necessary ESP-IDF libraries
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"


#define TAG_RVIZ "ROSSERIAL_RVIZ"
#define pi 3.141592653589


// callback functions called when publisher publishes the message
void message_callback(const sensor_msgs::JointState &msg);

// Subscriber to the joint controller messages
ros::Subscriber<sensor_msgs::JointState> arm("joint_states", &message_callback);

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

void message_callback(const sensor_msgs::JointState &msg)
{
    ESP_LOGD(TAG_RVIZ, "%s", "new message from publisher");

    ESP_LOGD(TAG_RVIZ, "timestamp:        %d", msg.header.seq);
    ESP_LOGD(TAG_RVIZ, "angle [BASE}:     %f", msg.position[0]);
    ESP_LOGD(TAG_RVIZ, "angle [SHOUDLER]: %f", msg.position[1]);
    ESP_LOGD(TAG_RVIZ, "angle [ELBOW]:    %f", msg.position[2]);

    set_angle_servo(&servo_c,msg.position[0]);
    set_angle_servo(&servo_b,msg.position[1]);
    set_angle_servo(&servo_a,msg.position[2]);
}

void rosserial_setup()
{
    ESP_LOGD(TAG_RVIZ, "%s", "ros controlled arm through rviz\n\n");
    
    nh.initNode();
    nh.subscribe(arm);
}

void rosserial_spinonce()
{
    nh.spinOnce();
}
