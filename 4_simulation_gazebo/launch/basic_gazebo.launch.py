#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_prefix

def generate_launch_description():
    pkg_ign_gazebo = get_package_share_directory('ros_ign_gazebo')
    pkg_mario_bot = get_package_share_directory('simulation_gazebo')

    description_package_name = "simulation_gazebo"
    install_dir = get_package_prefix(description_package_name)
    gazebo_models_path = os.path.join(pkg_mario_bot, 'models')

    if 'IGN_GAZEBO_RESOURCE_PATH' in os.environ:
        os.environ['IGN_GAZEBO_RESOURCE_PATH'] = os.environ['IGN_GAZEBO_RESOURCE_PATH'] + ':' + install_dir + '/share' + ':' + gazebo_models_path
    else:
        os.environ['IGN_GAZEBO_RESOURCE_PATH'] = install_dir + '/share' + ':' + gazebo_models_path

    # Launch Ignition Gazebo
    ign_gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ign_gazebo, 'launch', 'ign_gazebo.launch.py'),
        ),
        launch_arguments={'ign_args': '-r empty.sdf'}.items()
    )

    # Include mario launch
    mario = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_mario_bot, 'launch', 'mario.launch.py'),
        )
    )

    return LaunchDescription([
        ign_gazebo,
        mario
    ])
