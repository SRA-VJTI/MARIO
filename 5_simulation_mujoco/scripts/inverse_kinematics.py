#!/usr/bin/python3
import rclpy
from rclpy.node import Node
import inverse_kinematics_module
from std_msgs.msg import Float64MultiArray
from rclpy import qos
import math
import sys

def inverse_kinematics_publisher():
    Joints = node.create_publisher(Float64MultiArray, '/forward_position_controller/commands',qos_profile=qos.qos_profile_parameter_events)
    joint = Float64MultiArray()
    joint.data = [0.0,0.0,0.0,0.0,0.0]

    #Input coordinates
    x = float(input("Enter x: "))
    y = float(input("Enter y: "))
    z = float(input("Enter z: "))

    angle = inverse_kinematics_module.compute_angles(x,y,z)

    # Sending, if angles are in range of servos i.e 0 to 180
    index = -1
    count = 0
    print(angle)
    if angle[0][0] != None and angle[0][1] != None and angle[0][2] != None:
        if 0.0 <= int(angle[0][0]) <= 180.0 and 0.0 <= int(angle[0][1]) <= 180.0 and 0.0 <= int(angle[0][2]) <= 180.0:
            # angles_found = True
            index = 0
            count += 1

        if 0.0 <= int(angle[1][0]) <= 180.0 and 0.0 <= int(angle[1][1]) <= 180.0 and 0.0 <= int(angle[1][2]) <= 180.0:
            # angles_found = True
            index = 1
            count += 1

    if index != -1:

        #Print Joint angles
        print ("*************************")
        print ("{:15s}{:15s}{:15s}".format("theta_base", "theta_shoulder", "theta_elbow"))
        print ("{:<15f}{:<15f}{:<15f}".format(angle[0][0], angle[0][1], angle[0][2]))
        print ("{:<15f}{:<15f}{:<15f}".format(angle[1][0], angle[1][1], angle[1][2]))
        # Send angles
        if(count == 2):
            # To handle redundancy
            # Always sending those angles having approach vector as (0, 0, 1)
            # Condition for that is theta_shoulder + theta_elbow should be odd multiple of 180
            if (int(angle[0][1]) + int(angle[0][2])) % (2 * 180) != 0 and (int(angle[0][1]) + int(angle[0][2])) % 180 == 0:
                index = 0

            elif (int(angle[1][1]) + int(angle[1][2])) % (2 * 180) != 0 and (int(angle[1][1]) + int(angle[1][2])) % 180 == 0:
                index = 1

        #Converting Degrees to Radians
        joint.data[0] = (int(angle[index][0]))*math.pi/180
        joint.data[1] = (int(angle[index][1]))*math.pi/180
        joint.data[2] = (int(angle[index][2]))*math.pi/180

        #Publishing Joint angle Values
        Joints.publish(joint)
        print ("=========================\n")

    else:
        # Print error message
        print ("Angles not sent due to constraints")
        print ("Please enter points in range")


if __name__ == '__main__':

    rclpy.init(args=sys.argv)
    global node 
    node = Node('inverse_kinematics_publisher')
    node.create_timer(0.2, inverse_kinematics_publisher)
    rclpy.spin(node)
    rclpy.shutdown()
