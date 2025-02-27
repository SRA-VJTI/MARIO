#!/bin/bash

# Update package lists
sudo apt update

# Install ROS 2 Humble (assuming it's already installed)
# sudo apt install ros-humble-desktop

# Install Ignition Fortress
sudo apt install ignition-fortress -y

# Install ROS 2 Ignition Bridge and related packages
sudo apt install ros-humble-ros-ign -y
sudo apt install ros-humble-ign-ros2-control -y
sudo apt install ros-humble-ros-ign-gazebo -y

# Install additional ROS 2 dependencies
sudo apt install ros-humble-xacro -y
sudo apt install ros-humble-robot-state-publisher -y
sudo apt install ros-humble-joint-state-broadcaster -y
sudo apt install ros-humble-joint-trajectory-controller -y
sudo apt install ros-humble-forward-command-controller -y
sudo apt install ros-humble-rviz2 -y

sudo apt install -y ros-humble-ros2-control
sudo apt install -y ros-humble-joint-state-publisher-gui

# Source ROS 2 environment
source /opt/ros/humble/setup.bash

echo "Dependencies installed successfully!"
