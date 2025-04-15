# MARIO WORKSHOP 2.3

[![Downloads](https://static.pepy.tech/badge/MARIO/month)](https://pepy.tech/project/MARIO)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub star chart](https://img.shields.io/github/stars/SRA-VJTI/MARIO?style=social)](https://star-history.com/#SRA-VJTI/MARIO)
[![Dependency Status](https://img.shields.io/librariesio/github/SRA-VJTI/MARIO)](https://libraries.io/github/SRA-VJTI/MARIO)
[![Open Issues](https://img.shields.io/github/issues-raw/SRA-VJTI/MARIO)](https://github.com/SRA-VJTI/MARIO/issues)
[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/SRA-VJTI/MARIO)

*MARIO* abbreviation for *Manipulator on ROS Based Input Output* is a bot with 3 Degree of Freedom. It consists of two SG90 micro servo and one MG995 metal gear servo motor. The servo motors are placed on base, elbow and shoulder enabling it with 3 Degrees of Freedom.

Given below are instructions for ROS2-Humble and micro-ROS installations. For ROS1 and Rosserial based MARIO, refer to the [following instructions](https://github.com/SRA-VJTI/MARIO/tree/noetic).

## Sneak Peek


<p align="center"><img src="assets/bot2.png" style="width: 500px; height: auto;"></p>


### Working of the Mario Bot

<p align="center"><img src="assets/simulation_mario_v2.3.gif" width="480" height="848"></p>

### Mario bot simulated using Gazebo

<p align="center"><img src="assets/simulation.png"></p>



## File Structure
    ├── 1_chatter_listener                        # talker and listener script to understand the nodes and communications in ROS
    ├── 2_simulation_dh                           # simulation of DH paramteres
    ├── 3_simulation_rviz                         # simulation of MARIO bot on rviz
    ├── 4_simulation_gazebo                       # simulation of MARIO bot on gazebo
    ├── assets                                    # contains necessary gifs, images
    ├── firmware                                  # contains ESP-IDF examples for controlling servo motors and micro-ROS
    │   ├── 1_servo_set_zero                      # example in ESP-IDF to set angles of all servo motor zero
    │   ├── 2_servo_sweep                         # example in ESP-IDF to set variable angles in servo motor
    │   ├── 3_microros_rviz                       # example in ESP-IDF to interface with rviz environment as well as ESP32
    │   ├── 4_microros_gazebo                     # example in ESP-IDF to interface with gazebo environment as well as ESP32
    │   ├── 5_servo_test_webserver                # example in ESP-IDF to set angles of servo over the webserver interface
    │   └── components                            # contains all the dependencies required for the above examples
    │       ├── micro_ros_espidf_component        # library to interface between micro-ROS environment and ESP32
    │       └── sra-board-component               # library to interface with SRA board
    ├── LICENSE
    └── README.md

## Kinematics
* MARIO workshop aims to provide the basic knowledge about the DH parameters, forward kinematics , inverse kinematics.
  * DH Parameters :- Denavit–Hartenberg parameters (also called DH parameters) are the four parameters associated with a particular convention for attaching reference frames to the links of a spatial kinematic chain, or robot manipulator
  * Forward Kinematics :- Forward kinematics refers to the use of the kinematic equations of a robot to compute the position of the end-effector from specified values for the joint parameters. The kinematics equations of the robot are used in robotics, computer games, and animation.
  * Inverse Kinematics :- inverse kinematics is the mathematical process of calculating the variable joint parameters needed to place the end of a kinematic chain, such as a robot manipulator or animation character's skeleton, in a given position and orientation relative to the start of the chain.

## ROS-2
ROS2 is the ultimate toolkit for robotics enthusiasts and professionals alike. Seamlessly integrating hardware and software, ROS2 streamlines development workflows, accelerates prototyping, and enables rapid iteration. With its modular architecture and extensive library of reusable components, ROS2 simplifies the creation of complex robotics projects, from autonomous drones to collaborative robot arms.


## Publisher and Subscriber
Publish/Subscribe is a messaging pattern that aims to decouple the sending (Publisher) and receiving (Subscriber) party. A real world example could be a sport mobile app that shows you up-to-date information of a particular football game you're interested in. In this case you are the subscriber, as you express interest in this specific game. On the other side sits the publisher, which is an online reporter that feeds a system with the actual match data.
This system, which is often referred as the message broker brings the two parties together by sending the new data to all interested subscribers.

While ROS2 works on the same system, this system is also used in various other libraries like MQTT.


# MICRO-ROS
micro-ROS is a robotic framework targeting embedded and deep-embedded robot components with extremely constrained computational resources. These devices have special characteristics: a minimum real-time operating system or no operating system, battery-powered, wireless low bandwidth connections, and intermittent operation with sleep periods.


## ESP-IDF
ESP-IDF is the development framework for Espressif SoCs.The [SRA Board](https://github.com/SRA-VJTI/sra-board-hardware-design) uses ESP32 as microcontroller, hence ESPIDF is required
to code the ESP32. Examples included inside firmware directory has been written in ESPIDF version 5.1 .

## Installation

Choose the installation method appropriate for your operating system.

### Linux (Ubuntu/Debian based)

**Method 1: Quick Install (Recommended)**

- Copy and execute the following command in your terminal:
  ```bash
  wget -O - https://raw.githubusercontent.com/SRA-VJTI/MARIO/humble/linux_install.sh | bash
  ```

**Method 2: Manual Install**

- Clone SRA-VJTI's MARIO repository on your system:
  ```bash
  git clone --recursive https://github.com/SRA-VJTI/MARIO.git
  ```
- Change terminal directory inside the cloned repository:
  ```bash
  cd MARIO/
  ```
- Run the Linux installation script:
  ```bash
  ./linux_install.sh
  ```
