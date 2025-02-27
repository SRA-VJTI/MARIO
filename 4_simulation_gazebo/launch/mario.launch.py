#!/usr/bin/python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, RegisterEventHandler
from launch.substitutions import Command
from launch_ros.actions import Node
from launch.event_handlers import OnProcessStart, OnProcessExit
from launch_ros.descriptions import ParameterValue

def generate_launch_description():
    urdf_file = 'manipulator.urdf'
    package_description = "simulation_gazebo"

    config = os.path.join(
        get_package_share_directory('simulation_gazebo'),
        'config',
        'manipulator.yaml'
    )
    
    robot_desc_path = os.path.join(get_package_share_directory(package_description), "urdf", urdf_file)
    robot_description_content = Command(['xacro ', robot_desc_path])
    robot_description = {"robot_description": ParameterValue(robot_description_content, value_type=str)}

    # ROS 2 Control Node
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[robot_description, config],
        output="both",
    )

    # Joint State Broadcaster
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    )

    # Forward Position Controller
    robot_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["forward_position_controller", "-c", "/controller_manager"],
    )

    # Robot State Publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        emulate_tty=True,
        parameters=[{'use_sim_time': True, 'robot_description': robot_description['robot_description']}],
        output="screen"
    )

    # Spawn the robot in Ignition Gazebo
    spawn_robot = Node(
        package='ros_ign_gazebo',
        executable='create',
        name='spawn_entity',
        output='screen',
        arguments=['-topic', '/robot_description',
                   '-entity', 'mario',
                   '-x', '0.0', '-y', '0.0', '-z', '0.0',
                   '-R', '0.0', '-P', '0.0', '-Y', '0.0']
    )

    # Event handlers for sequencing
    delay_joint_state_broadcaster = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=spawn_robot,
            on_exit=[joint_state_broadcaster_spawner],
        )
    )
    
    delay_robot_controller = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[robot_controller_spawner],
        )
    )

    return LaunchDescription([
        control_node,
        robot_state_publisher_node,
        spawn_robot,
        delay_joint_state_broadcaster,
        delay_robot_controller
    ])
