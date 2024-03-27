#!/usr/bin/python3
#without GUI
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument,  ExecuteProcess, RegisterEventHandler
from launch.substitutions import Command
from launch_ros.actions import Node
import launch_ros.actions
from launch.event_handlers import (OnProcessStart, OnProcessExit)
from launch_ros.descriptions import ParameterValue
import random

# this is the function launch  system will look for
def generate_launch_description():
    ####### DATA INPUT ##########
    urdf_file = 'manipulator.urdf'
    package_description = "simulation_rviz"
    ####### DATA INPUT END ##########
    config = os.path.join( get_package_share_directory('simulation_rviz'),
    'config',
    'manipulator.yaml'
    )
    robot_desc_path = os.path.join(get_package_share_directory(package_description), "urdf", urdf_file)
    print("Fetching URDF ==>")
    
    # Robot State Publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        emulate_tty=True,
        parameters=[{'use_sim_time': True, '-r': 10, 'robot_description': ParameterValue(Command(['xacro ',robot_desc_path]), value_type=str)}],
        output="screen"
    )
 
    rviz_launch = Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time' : True}],
            arguments=['-d' + os.path.join(get_package_share_directory(package_description), 'rviz', 'manipulator.rviz')]
        )
     # This node is to publish static funtion values of base link to link 1
    tf2_link1 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["-0.0030196", "0.046937", "0.0635", "0", "0", "0", "base_link", "link_1"]
        )
     # This node is to publish static funtion values of link 1 to link 2
    tf2_link2 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.00031511", "-0.0095653", "0.034407", "0", "0", "0", "link_1", "link_2"]
        )
     # This node is to publish static funtion values of link 2 to link 3
    tf2_link3 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.071531", "0.011279", "-0.0041348", "0", "0", "0", "link_2", "link_3"]
        )
     # This node is to publish static funtion values of link 3 to link claw_right
    tf2_claw_right = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.020925", "-0.013767", "-0.090331", "0", "0", "0", "link_3", "claw_right"]
        )
     # This node is to publish static funtion values of claw_right to claw_left
    tf2_claw_left = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.0091023", "0.0182709", "-0.090512", "0", "0", "0", "link_3", "claw_left"]
        )
  
    print("==> Using Sim time\n")
    return LaunchDescription([  
        tf2_link1,tf2_link2,tf2_link3,tf2_claw_left,tf2_claw_right,
        robot_state_publisher_node,
        rviz_launch,
    ])
