#!/usr/bin/env python

import rospy
from std_msgs.msg import String

import sys

def talker():
    #Assign topic to the publisher
    pub = rospy.Publisher('chatter', String, queue_size=10)
    
    #Initialise node for publisher
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)	#10hz

    while not rospy.is_shutdown():
        msg = raw_input("")
        
        if msg == "exit" or msg == "Exit" or msg == "EXIT" :
            print "exiting..."
            sys.exit()
        else :

            #Publish message to the Topic
            pub.publish(msg)
            rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: 
        pass
