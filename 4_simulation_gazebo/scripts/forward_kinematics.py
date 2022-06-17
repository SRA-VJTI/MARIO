#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rospy
from std_msgs.msg import Float64
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
joint = [0.0, 0.0, 0.0, 0.0, 0.0]  

def forward_kinematics_publisher():

    Joint_1 = rospy.Publisher('/manipulator/joint_1_controller/command',Float64, queue_size=10)
    Joint_2 = rospy.Publisher('/manipulator/joint_2_controller/command',Float64, queue_size=10)
    Joint_3 = rospy.Publisher('/manipulator/joint_3_controller/command',Float64, queue_size=10)
    Joint_4 = rospy.Publisher('/manipulator/joint_4_controller/command',Float64, queue_size=10)
    Joint_5 = rospy.Publisher('/manipulator/joint_5_controller/command',Float64, queue_size=10)
    rospy.init_node('forward_kinematics_publisher', anonymous=True)
    rate = rospy.Rate(10)   #10hz
    while not rospy.is_shutdown():
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

        if 0.0 <= theta_base <= 180.0 and 0.0 <= theta_shoulder <= 180.0 and 0.0 <= theta_elbow <= 180.0: 
            joint[0] = (theta_base)*math.pi/180
            joint[1] = (theta_shoulder)*math.pi/180
            joint[2] = (theta_elbow)*math.pi/180
            if gripper_open:
                joint[3] = 0.8
                joint[4] = 0.8
            else:
                joint[3] = 0.0
                joint[4] = 0.0

            rospy.loginfo("\ntheta_base = %f\ntheta_shoulder = %f\ntheta_elbow = %f\ngripper_open = %f", joint[0], joint[1], joint[2], gripper_open)
            Joint_1.publish(joint[0])
            Joint_2.publish(joint[1])
            Joint_3.publish(joint[2])
            Joint_4.publish(joint[3])
            Joint_5.publish(joint[4])


            print ("=========================\n")

        else:
            print ("Enter angles in range 0 to 180")
        rate.sleep()


if __name__ == '__main__':
    try:
        forward_kinematics_publisher()
    except rospy.ROSInterruptException: 
        pass