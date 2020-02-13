#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Vector3
import sys
import math
import numpy as np

##Variables
d0 = 2.5
a1 = 12
d3 = 9.5

def compute_co_ordinates(theta,d=[d0,0,0,d3],alpha=[math.pi/2,0,math.pi/2,0],a=[0,a1,0,0]):
    
    for i in range(4):
        theta[i] = math.radians(theta[i])
    
    #Creation and multiplication of transformation matrices
    transformation_matrix_0_to_4 = [[1,0,0,0], [0,1,0,0], [0,0,1,0], [0,0,0,1]]

    for i in range(len(d)):

        transformation = np.matrix([[math.cos(theta[i]),-math.cos(alpha[i])*math.sin(theta[i]),math.sin(alpha[i])*math.sin(theta[i]),a[i]*math.cos(theta[i])], [math.sin(theta[i]),math.cos(alpha[i])*math.cos(theta[i]),-math.sin(alpha[i])*math.cos(theta[i]),a[i]*math.sin(theta[i])], [0,math.sin(alpha[i]),math.cos(alpha[i]),d[i]], [0,0,0,1]])

        # print("{}\n transformation from {} to {}".format(transformation, i, i+1))

        transformation_matrix_0_to_4 *= transformation

    return transformation_matrix_0_to_4

def talker():

    pub_array = rospy.Publisher('ros_arm_control', Vector3, queue_size=10) 
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)	#10hz
    msg = Vector3()

    while not rospy.is_shutdown():
        t0 = float(input("Enter theta0 "))
        t1 = float(input("Enter theta1 "))
        t2 = float(input("Enter theta2 "))

        transformationMatrix = compute_co_ordinates([t0,t1,t2,0])
        print (transformationMatrix[0,3],transformationMatrix[1,3],transformationMatrix[2,3]) 

        # coordinate_str = str(t0) + " " + str(t1) + " " + str(t2) + " "
        msg.x = t0
        msg.y = t1
        msg.z = t2

        rospy.loginfo(msg)
        pub_array.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: 
        pass