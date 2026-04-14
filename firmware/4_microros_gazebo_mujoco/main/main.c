/*
MIT License

Copyright (c) 2024 Society of Robotics and Automation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"

#include <uros_network_interfaces.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <std_msgs/msg/float64_multi_array.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <sra_board.h>

#ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
#include <rmw_microros/rmw_microros.h>
#endif

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);vTaskDelete(NULL);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

#define ARRAY_LEN 200
#define JOINT_DOUBLE_LEN 5
#define pi 3.141592653589
#define SMOOTHING_STEPS 20  // Number of intermediate steps
#define SMOOTHING_DELAY 20  // Delay between steps in milliseconds

// Structure to track current positions
typedef struct {
    float current_base;
    float current_shoulder;
    float current_elbow;
    float current_gripper;
} servo_positions;

static servo_positions current_pos = {0, 0, 0, 0};

rcl_subscription_t subscriber;
std_msgs__msg__Float64MultiArray recv_msg;

char test_array[ARRAY_LEN];

// Servo configurations
servo_config servo_a = {        //GRIPPER
    .servo_pin = SERVO_A,
    .min_pulse_width = CONFIG_SERVO_A_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_A_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_A_MAX_DEGREE,

};

servo_config servo_b = {        //ELBOW
    .servo_pin = SERVO_B,
    .min_pulse_width = CONFIG_SERVO_B_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_B_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_B_MAX_DEGREE,

};

servo_config servo_c = {        //ARM
    .servo_pin = SERVO_C,
    .min_pulse_width = CONFIG_SERVO_C_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_C_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_C_MAX_DEGREE,

};

servo_config servo_d = {        //BASE
    .servo_pin = SERVO_D,
    .min_pulse_width = CONFIG_SERVO_D_MIN_PULSEWIDTH,
    .max_pulse_width = CONFIG_SERVO_D_MAX_PULSEWIDTH,
    .max_degree = CONFIG_SERVO_D_MAX_DEGREE,

};

// Function to smoothly move servo from current to target position
void smooth_servo_motion(servo_config *servo, float current_angle, float target_angle) {
    float angle_diff = target_angle - current_angle;
    float step = angle_diff / SMOOTHING_STEPS;

    for(int i = 0; i < SMOOTHING_STEPS; i++) {
        float intermediate_angle = current_angle + (step * (i + 1));
        set_angle_servo(servo, intermediate_angle);
        vTaskDelay(pdMS_TO_TICKS(SMOOTHING_DELAY));
    }
}

void subscription_callback(const void * msgin)
{
    const std_msgs__msg__Float64MultiArray * msg = (const std_msgs__msg__Float64MultiArray *)msgin;

    // Convert radians to degrees
    float target_base = msg->data.data[0] * (180/pi);
    float target_shoulder = msg->data.data[1] * (180/pi);
    float target_elbow = msg->data.data[2] * (180/pi);
    float target_gripper = ((1.57-msg->data.data[3]) * (180/pi)); // Modified calculation for gripper servo

    // Apply smooth motion to each servo if change is significant
    if (fabs(target_base - current_pos.current_base) > 0.5) {
        smooth_servo_motion(&servo_d, current_pos.current_base, target_base);
        current_pos.current_base = target_base;
    }

    if (fabs(target_shoulder - current_pos.current_shoulder) > 0.5) {
        smooth_servo_motion(&servo_c, current_pos.current_shoulder, target_shoulder);
        current_pos.current_shoulder = target_shoulder;
    }

    if (fabs(target_elbow - current_pos.current_elbow) > 0.5) {
        smooth_servo_motion(&servo_b, current_pos.current_elbow, target_elbow);
        current_pos.current_elbow = target_elbow;
    }

    if (fabs(target_gripper - current_pos.current_gripper) > 0.5) {
        smooth_servo_motion(&servo_a, current_pos.current_gripper, target_gripper);
        current_pos.current_gripper = target_gripper;
    }
}

void micro_ros_task(void * arg)
{
    printf("Starting micro-ROS task\n");
    memset(test_array, 'z', ARRAY_LEN);
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rclc_support_t support;

    // Enable servo and initialize current positions
    enable_servo();
    current_pos.current_gripper = read_servo(&servo_a);
    current_pos.current_elbow = read_servo(&servo_b);
    current_pos.current_shoulder = read_servo(&servo_c);
    current_pos.current_base = read_servo(&servo_d);

    // Create init_options
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    RCCHECK(rcl_init_options_init(&init_options, allocator));

    #ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
    rmw_init_options_t* rmw_options = rcl_init_options_get_rmw_init_options(&init_options);
    RCCHECK(rmw_uros_options_set_udp_address(CONFIG_MICRO_ROS_AGENT_IP, CONFIG_MICRO_ROS_AGENT_PORT, rmw_options));
    #endif

    // Setup support structure
    RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));

    // Create node
    rcl_node_t node = rcl_get_zero_initialized_node();
    RCCHECK(rclc_node_init_default(&node, "Set_servo_angles", "", &support));

    // Create subscriber
    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float64MultiArray),
        "/forward_position_controller/commands"));

    // Create executor
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));

    unsigned int rcl_wait_timeout = 1000;   // in ms
    RCCHECK(rclc_executor_set_timeout(&executor, RCL_MS_TO_NS(rcl_wait_timeout)));

    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &recv_msg, &subscription_callback, ON_NEW_DATA));

    // Allocate memory for received message
    recv_msg.data.data = (double*) malloc(ARRAY_LEN);
    recv_msg.data.size = 0;
    recv_msg.data.capacity = ARRAY_LEN;

    // Spin forever
    rclc_executor_spin(&executor);

    // Cleanup
    RCCHECK(rcl_subscription_fini(&subscriber, &node));
    RCCHECK(rcl_node_fini(&node));

    vTaskDelete(NULL);
}

void app_main(void)
{
    #if defined(CONFIG_MICRO_ROS_ESP_NETIF_WLAN) || defined(CONFIG_MICRO_ROS_ESP_NETIF_ENET)
    ESP_ERROR_CHECK(uros_network_interface_initialize());
    #endif

    xTaskCreate(micro_ros_task,
            "uros_task",
            CONFIG_MICRO_ROS_APP_STACK,
            NULL,
            CONFIG_MICRO_ROS_APP_TASK_PRIO,
            NULL);
}
