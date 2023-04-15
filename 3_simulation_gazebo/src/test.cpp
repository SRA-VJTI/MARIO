#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "bits/stdc++.h"
#include "chrono"

// Define PID gains
double kp[5] = {100, 50, 10 , 0.1, 0.1};
double ki[5] = { 0 , 0 , 0.1,  0 ,  0 };
double kd[5] = {0.1,0.5,0.01,  0 ,  0 };

double prev_error[5] = {0};

auto current_time = std::chrono::system_clock::now();
auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
double num_seconds = duration_in_seconds.count();

double prev_time[5] = {num_seconds};
std::vector<double> current_angles;
double integral[5] = {0};    

/*
    Function        : get_joint_efforts
    Arguments       : desired angles (Array in form of `double`)
    Functionality   : Implements PID on the given angles to get the effort for bot to maintain its poisiton
    Returns         : returns efforts for each joints
*/
std::vector<double> get_joint_efforts(std::vector<double> desired_angles){
    // Assuming you have obtained the current joint angle, desired joint angle, and time step

    std::vector<double> efforts(5);
    for ( int i = 0 ; i < 5 ; i++ ){
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

        auto value = now_ms.time_since_epoch();
        uint64_t seconds = value.count();
        std::cout<<seconds;
        
        double current_angle = current_angles[i];
        double desired_angle = desired_angles[i];
        double time_step = ( seconds - prev_time[i] ) / 1000;
        // Define curr_error terms
        double curr_error = desired_angle - current_angle;
        double derivative = (curr_error - prev_error[i]) / time_step;

        // Compute PID control effort
        double desired_effort = kp[i] * curr_error + ki[i] * integral[i] + kd[i] * derivative;
        std::cout<<desired_effort;
        efforts[i] = desired_effort;
        // Update integral and error terms for next iteration
        integral[i] += curr_error * time_step;
        if ( integral[i] > 0.1 ){
            integral[i] = 0;
        }
        prev_error[i] = curr_error;
        prev_time[i] = seconds;
    }

    return efforts;

}

/*  
    Function        : Callback
    Arguments       : Message pointer of type JointState
    Functionality   : stores the data from JointState topic into current angles
*/
void callback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    // Callback function to handle received messages
    for ( int i = 0 ; i < 5 ; i++ ){
        current_angles[i] = msg->position[i];
    }
}

std::shared_ptr<rclcpp::Node> node;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    node = std::make_shared<rclcpp::Node>("effort_test_node");

    auto publisher = node->create_publisher<std_msgs::msg::Float64MultiArray>(
        "/effort_controllers/commands", 10);

    auto subscriber = node->create_subscription<sensor_msgs::msg::JointState>(
    "/joint_states", 10, callback);

    RCLCPP_INFO(node->get_logger(), "node created");

    std::vector<double> desired_angles(5);

    std::cout << " Enter Desired Angles for 5 Joints : \n";

    for(int i = 0 ; i < 5 ; i ++){
        double desired_angle;
        printf(" Joint %d : ", i+1);
        scanf("%lf", &desired_angle);
        desired_angles.push_back(desired_angle);
    }

    std_msgs::msg::Float64MultiArray commands;
    commands.data.clear();
    commands.data.resize(5);
    rclcpp::Rate r(10);

    while(rclcpp::ok()){
        
        std::cout<<"hi\n";
        std::vector<double> efforts = get_joint_efforts(desired_angles);
        for ( int i = 0 ; i < 5 ; i ++){
            commands.data[i] = efforts[i];
        }

        publisher->publish(commands);

        rclcpp::spin(node);
        r.sleep();
    }
    rclcpp::shutdown();
    return 0;
}