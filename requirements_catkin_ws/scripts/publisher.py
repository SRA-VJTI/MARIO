#!/usr/bin/env python

import rospy
import sys
from sra.msg import custom_array ##custom message

def publisher():

    publisher = rospy.Publisher('array', custom_array, queue_size=10) 
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)	#10hz
    custom_msg = custom_array()

    while not rospy.is_shutdown():
        
        theta_base = int(input("{:22s}".format("Enter theta_base: ")))
        theta_shoulder = int(input("{:22s}".format("Enter theta_shoulder: ")))
        theta_elbow = int(input("{:22s}".format("Enter theta_elbow: ")))

        custom_msg.array1.append(theta_base)
        custom_msg.array1.append(theta_shoulder)
        custom_msg.array1.append(theta_elbow)

        rospy.loginfo(custom_msg)
        publisher.publish(custom_msg)
        custom_msg.array1 = []
        rate.sleep()
        

if __name__ == '__main__':
    try:
        publisher()
    except rospy.ROSInterruptException: 
        pass








    