#include "ros.h"
// #include "geometry_msgs/Vector3.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/JointState.h"
#include "esp_serial.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

servo_config servo_a = {
	.servo_pin = SERVO_A,
	.min_pulse_width = CONFIG_SERVO_A_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_A_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_A_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_A,
};

servo_config servo_b = {
	.servo_pin = SERVO_B,
	.min_pulse_width = CONFIG_SERVO_B_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_B_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_B_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_0,
	.gen = MCPWM_OPR_B,
};

servo_config servo_c = {
	.servo_pin = SERVO_C,
	.min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
	.max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
	.max_degree = CONFIG_SERVO_C_MAX_DEGREE,
	.mcpwm_num = MCPWM_UNIT_0,
	.timer_num = MCPWM_TIMER_1,
	.gen = MCPWM_OPR_A,
};

//////////////////////////////////////////////////////////////////////////////
static const char* TAG_C = "ros_control";
static const char* TAG_RVIZ = "ros_control_rviz";
void message_callback1(const std_msgs::Float64 &msg);
void message_callback2(const std_msgs::Float64 &msg);
void message_callback3(const std_msgs::Float64 &msg);
void message_callback_rviz(const sensor_msgs::JointState &msg);
ros::NodeHandle nh;
// ros::Subscriber<geometry_msgs::Vector3> arm("ros_arm_control", &message_callback);
ros::Subscriber<std_msgs::Float64> arm1("/manipulator/joint_1_controller/command", &message_callback1);
ros::Subscriber<std_msgs::Float64> arm2("/manipulator/joint_2_controller/command", &message_callback2);
ros::Subscriber<std_msgs::Float64> arm3("/manipulator/joint_3_controller/command", &message_callback3);
ros::Subscriber<sensor_msgs::JointState> arm_rviz("joint_states", &message_callback_rviz);
//////////////////////////////////////////////////////////////////////////////

void message_callback1(const std_msgs::Float64 &msg)
{
    ESP_LOGD(TAG_C, "%s", "new message from publisher");

    ESP_LOGD(TAG_C, "angle [BASE]:     %f", msg.data);

    set_angle_servo(&servo_c,msg.data*(180/3.14));
}
void message_callback2(const std_msgs::Float64 &msg)
{
    ESP_LOGD(TAG_C, "%s", "new message from publisher");

    ESP_LOGD(TAG_C, "angle [SHOUDLER]: %f", msg.data);

    set_angle_servo(&servo_b,msg.data *(180/3.14));
}
void message_callback3(const std_msgs::Float64 &msg)
{
    ESP_LOGD(TAG_C, "%s", "new message from publisher");

    ESP_LOGD(TAG_C, "angle [ELBOW]:    %f", msg.data);

    set_angle_servo(&servo_a,msg.data*(180/3.14));
}

void rosserial_setup()
{
    ESP_LOGD(TAG_C, "%s", "ros controlled arm through custom publisher\n\n");
    
    nh.initNode();                  // Initialize ROS
    nh.subscribe(arm1);              // subscribe to topic
    nh.subscribe(arm2); 
    nh.subscribe(arm3); 
}

void rosserial_spinonce()
{
    nh.spinOnce();
}

void message_callback_rviz(const sensor_msgs::JointState &msg)
{
    ESP_LOGD(TAG_RVIZ, "%s", "new message from publisher");

    ESP_LOGD(TAG_RVIZ, "timestamp:        %d", msg.header.seq);
    ESP_LOGD(TAG_RVIZ, "angle [BASE}:     %f", msg.position[0]);
    ESP_LOGD(TAG_RVIZ, "angle [SHOUDLER]: %f", msg.position[1]);
    ESP_LOGD(TAG_RVIZ, "angle [ELBOW]:    %f", msg.position[2]);

    set_angle_servo(&servo_a,msg.position[0]);
	set_angle_servo(&servo_b,msg.position[1]);
	set_angle_servo(&servo_c,msg.position[2]);
}

void rosserial_setup_rviz()
{
    ESP_LOGD(TAG_RVIZ, "%s", "ros controlled arm through rviz\n\n");
    
    nh.initNode();
    nh.subscribe(arm_rviz);
}

void rosserial_spinonce_rviz()
{
    nh.spinOnce();
}
