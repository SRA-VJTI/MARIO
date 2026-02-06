#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='simulation_mujoco',
            executable='mujoco_ros2_bridge_box.py',
            name='mujoco_ros2_bridge',
            output='screen'
        ),
        
        Node(
            package='simulation_mujoco',
            executable='pick_n_place.py',
            name='pick_n_place',
            output='screen'
        ),
    ])