#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
from geometry_msgs.msg import Vector3
import math
import forward_kinematics_module

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
d = [2.5, 0, 0, 9.5]
alpha = [math.pi/2,0, math.pi/2, 0]
a = [0, 12, 0, 0]

def forward_kinematics_publisher():

    publisher_fk = rospy.Publisher('ros_arm_control', Vector3, queue_size=10) 
    rospy.init_node('forward_kinematics_publisher', anonymous=True)
    rate = rospy.Rate(10)   #10hz
    angles = Vector3()         #ROS message type

    while not rospy.is_shutdown():
        #Input angles
        theta_base = float(input("{:22s}".format("Enter theta_base: ")))
        theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
        theta_elbow = float(input("{:22s}".format("Enter theta_elbow: ")))
        theta = [theta_base, theta_shoulder, theta_elbow, 0]

        final_transformation_matrix = forward_kinematics_module.compute_coordinates(theta, d, alpha, a)
        
        #Print End-effector's Coordinates
        print "*************************"
        print "{:21s}".format("x-coordinate"), "{0:.5f}".format(final_transformation_matrix[0, 3])
        print "{:21s}".format("y-coordinate"), "{0:.5f}".format(final_transformation_matrix[1, 3])
        print "{:21s}".format("z-coordinate"), "{0:.5f}".format(final_transformation_matrix[2, 3])

        if 0.0 <= theta_base <= 180.0 and 0.0 <= theta_shoulder <= 180.0 and 0.0 <= theta_elbow <= 180.0: 
            angles.x = theta_base
            angles.y = theta_shoulder
            angles.z = theta_elbow

            rospy.loginfo("\ntheta_base = %f\ntheta_shoulder = %f\ntheta_elbow = %f", angles.x, angles.y, angles.z)
            publisher_fk.publish(angles)
            print "=========================\n"

        else:
            print "Enter angles in range 0 to 180"
        rate.sleep()

if __name__ == '__main__':
    try:
        forward_kinematics_publisher()
    except rospy.ROSInterruptException: 
        pass