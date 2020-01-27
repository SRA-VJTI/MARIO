#!/usr/bin/env python

import rospy

from sra.msg import custom_array ##custom message
import sys


def talker():

   
    pub_array = rospy.Publisher('array',custom_array, queue_size=10) 
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)	#10hz
    msg = custom_array()

    while not rospy.is_shutdown():
        
        t1 = int(input("Enter theta1 "))
        t2 = int(input("Enter theta2 "))
        t3 = int(input("Enter theta3 "))

        msg.array1.append(t1)
        msg.array1.append(t2)
        msg.array1.append(t3)

        rospy.loginfo(msg)
        pub_array.publish(msg)
        msg.array1 = []
        rate.sleep()
        

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: 
        pass








    