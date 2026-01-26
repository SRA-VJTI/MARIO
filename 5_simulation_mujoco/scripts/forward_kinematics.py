#!/usr/bin/python3
# -*- coding: utf-8 -*-
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import forward_kinematics_module
from rclpy import qos
import math
import sys

'''
+-----------------------+--------------+--------------+----------+--+
| Transformation Matrix |              |              |          |  |
+-----------------------+--------------+--------------+----------+--+
| cosθ                  | -cosα * sinθ | sinα * sinθ  | a * cosθ |  |
| sinθ                  | cosα * cosθ  | -sinα * cosθ | a * sinθ |  |
| 0                     | sinα         | cosα         | d        |  |
| 0                     | 0            | 0            | 1        |  |
+-----------------------+--------------+--------------+----------+--+
+-------------------+-----------------------------+------------------+-----------------------------+--+
|  θ (about Z axis) |      d (along Z axis)       | α (about X axis) |      a (along X axis)       |  |
+-------------------+-----------------------------+------------------+-----------------------------+--+
| theta_base        | d0 (base to shoulder - 2.5) | π/2              | 0                           |  |
| theta_shoulder    | 0                           | 0                | a1 (shoulder to elbow - 12) |  |
| theta_elbow       | 0                           | π/2              | 0                           |  |
| 0                 | d3 (elbow to end - 9.5)     | 0                | 0                           |  |
+-------------------+-----------------------------+------------------+-----------------------------+--+
'''

#Transformation Matrix Calculated Parameters
theta = []      #Since it will be user input
d = [10, 0, 0, 13]
alpha = [math.pi/2,0, math.pi/2, 0]
a = [0, 6, 0, 0]
joint = [0.0, 0.0, 0.0, 0.0, 0.0]

def forward_kinematics_publisher():

    global node

    Joints = node.create_publisher(Float64MultiArray, '/forward_position_controller/commands',qos_profile=qos.qos_profile_parameter_events)
    #Input angles
    theta_base = float(input("{:22s}".format("Enter theta_base: ")))
    theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
    theta_elbow = float(input("{:22s}".format("Enter theta_elbow: ")))
    gripper_open = float(input("{:22s}".format("Enter Gripper Position(0 - close/ 1 - open): ")))
    theta = [theta_base, theta_shoulder, theta_elbow, 0]

    final_transformation_matrix = forward_kinematics_module.compute_coordinates(theta, d, alpha, a)

    #Print End-effector's Coordinates
    print ("*************************")
    print ("{:21s}".format("x-coordinate"), "{0:.5f}".format(final_transformation_matrix[0, 3]))
    print ("{:21s}".format("y-coordinate"), "{0:.5f}".format(final_transformation_matrix[1, 3]))
    print ("{:21s}".format("z-coordinate"), "{0:.5f}".format(final_transformation_matrix[2, 3]))

    joint = Float64MultiArray()
    joint.data = [0.0,0.0,0.0,0.0,0.0]
    if 0.0 <= theta_base <= 180.0 and 0.0 <= theta_shoulder <= 180.0 and 0.0 <= theta_elbow <= 180.0:
        joint.data[0] =(theta_base)*math.pi/180
        joint.data[1] = (theta_shoulder)*math.pi/180
        joint.data[2] = (theta_elbow)*math.pi/180
        if gripper_open:
            joint.data[3] = 0.8
            joint.data[4] = 0.8
        else:
            joint.data[3] = 0.0
            joint.data[4] = 0.0

        print("\ntheta_base = ", joint.data[0], "\n", "theta_shoulder = " , joint.data[1], "\n", "theta_elbow = " , joint.data[2], "\n", "Gripper Open = " , gripper_open, "\n")

        print ("=========================\n")

    else:
        print ("Enter angles in range 0 to 180")

    Joints.publish(joint)

if __name__ == '__main__':
    rclpy.init(args=sys.argv)
    global node
    node = Node('forward_kinematics_publisher')
    node.create_timer(0.2, forward_kinematics_publisher)
    rclpy.spin(node)
    rclpy.shutdown()
