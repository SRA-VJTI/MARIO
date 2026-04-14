#!/usr/bin/env python3
import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_share = get_package_share_directory('simulation_mujoco')

    mujoco_bridge = Node(package='simulation_mujoco',executable='mujoco_ros2_bridge.py',name='mujoco_ros2_bridge',output='screen')  # launching bridge
    
    # forward_kinematics = Node(
    #     package='simulation_mujoco',
    #     executable='forward_kinematics.py',
    #     name='forward_kinematics',
    #     output='screen'
    # )

    return LaunchDescription([
        mujoco_bridge,             
        # forward_kinematics,       #auto launch kinematics node 
    ])