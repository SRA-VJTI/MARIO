#!/usr/bin/python3
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
    #xacro_file = "box_bot.xacro"robot_description
    package_description = "simulation_rviz"
    ####### DATA INPUT END ##########
    config = os.path.join( get_package_share_directory('simulation_rviz'),
    'config',
    'manipulator.yaml'
    )
    robot_desc_path = os.path.join(get_package_share_directory(package_description), "urdf", urdf_file)
    print("Fetching URDF ==>")

    # joint_state_publisher = Node(
    #         package="joint_state_publisher",
    #         executable="joint_state_publisher"
    #         )



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
    tf2_link1 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["-0.0030196", "0.046937", "0.0635", "0", "0", "0", "base_link", "link_1"]
        )
    tf2_link2 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.00031511", "-0.0095653", "0.034407", "0", "0", "0", "link_1", "link_2"]
        )

    tf2_link3 = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.071531", "0.011279", "-0.0041348", "0", "0", "0", "link_2", "link_3"]
        )
    
    tf2_claw_right = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.020925", "-0.013767", "-0.090331", "0", "0", "0", "link_3", "claw_right"]
        )
    
    tf2_claw_left = Node(
            package='tf2_ros',
            namespace='',
            executable='static_transform_publisher',
            arguments=["0.0091023", "0.0182709", "-0.090512", "0", "0", "0", "link_3", "claw_left"]
        )
    # load_joint_position_controller = ExecuteProcess(
    #     cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'position_controllers'],
    # output='screen'
    # )
    # create and return launch description object
    print("==> Using Sim time\n")
    return LaunchDescription([  
        # load_joint_position_controller,
        tf2_link1,tf2_link2,tf2_link3,tf2_claw_left,tf2_claw_right,
        robot_state_publisher_node,
        rviz_launch,
        # joint_state_publisher,
    ])