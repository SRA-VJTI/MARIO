#!/usr/bin/env python

import rospy
from std_msgs.msg import String
# from sra.msg import custom_array ##custom message
import sys
import math
import numpy as np

##Variables
initial_link_length = 2.5
correction_factor = 0
link_length = 12
link_length1 = 9.5

def compute_co_ordinates(theta_1,theta_2,theta_3):
    theta_2*=-1
    theta_3*=-1 
    theta_1 = math.radians(theta_1)
    theta_2 = math.radians(theta_2)

    #Servo shifted by 90 degrees
    theta_3 = math.radians(theta_3) + math.pi/2 
    

    #Creation and multiplication of transformation matrices
    transformation_matrix_0_to_1 = np.matrix([[math.cos(theta_1),0,-math.sin(theta_1),0],[math.sin(theta_1),0,math.cos(theta_1),0],[0,-1,0,initial_link_length],[0,0,0,1]])

    transformation_matrix_1_to_2 = np.matrix([[math.cos(theta_2),-math.sin(theta_2),0,link_length*math.cos(theta_2)],[math.sin(theta_2),math.cos(theta_2),0,link_length1*math.sin(theta_2)],[0,0,1,0],[0,0,0,1]])
    
    transformation_matrix_2_to_3 = np.matrix([[math.cos(theta_3),-math.sin(theta_3),0,link_length*math.cos(theta_3)],[math.sin(theta_3),math.cos(theta_3),0,link_length1*math.sin(theta_3)],[0,0,1,correction_factor],[0,0,0,1]])   
    
    transformation_matrix_0_to_3 = transformation_matrix_0_to_1*transformation_matrix_1_to_2*transformation_matrix_2_to_3

    return transformation_matrix_0_to_3

def compute_angles(t1,t2,t3):
    
    theta_1 = t1
    theta_2 = t2
    theta_3 = t3
    return theta_1, theta_2, theta_3 


def talker():

    pub_array = rospy.Publisher('ros_arm_control',String, queue_size=10) 
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)	#10hz
    msg = String()

    while not rospy.is_shutdown():
       
        
        t1 = int(input("Enter theta1 "))
        t2 = int(input("Enter theta2 "))
        t3 = int(input("Enter theta3 "))

        transformationMatrix = compute_co_ordinates(t1,t2,t3)
        print (transformationMatrix[0,3],transformationMatrix[1,3],transformationMatrix[2,3]) 

        cord_str = str(t1) + " " + str(t2) + " " + str(t3) + " "
        msg.data = cord_str

        rospy.loginfo(msg)
        pub_array.publish(msg)
        msg.data = ""
        rate.sleep()
        

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: 
        pass








    
