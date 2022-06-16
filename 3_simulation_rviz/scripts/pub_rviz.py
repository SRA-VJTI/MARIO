#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import JointState
from std_msgs.msg import Header
import math

def talker():
    pub = rospy.Publisher('joint_states', JointState, queue_size=10)
    rospy.init_node('joint_state_bhau' , anonymous=False)
    rate = rospy.Rate(10) # 10hz
    default = JointState()
    default.header = Header()
    default.header.stamp = rospy.Time.now()
    default.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5']
    default.position = [0.0, 0.0, 0.0, 0.0, 0.0]
    default.velocity = []
    default.effort = []
    pub.publish(default)
    while not rospy.is_shutdown():
        hello_str = JointState()
        hello_str.header = Header()
        hello_str.header.stamp = rospy.Time.now()

        theta_base = float(input("{:22s}".format("Enter theta_base: ")))
        theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
        theta_elbow = float(input("{:22s}".format("Enter theta_elbow: ")))
        theta_claw1 = float(input("{:22s}".format("Enter theta_claw 1: ")))
        theta_claw2 = float(input("{:22s}".format("Enter theta_claw 2: ")))
        
        if 0 <= theta_base <= 180.0 and 0 <= theta_shoulder <= 180.0 and 0 <= theta_elbow <= 180.0 and 0.0 <= theta_claw1 <= 180.0 and 0.0 <= theta_claw2 <= 180.0 : 
            theta_base = (theta_base)*math.pi/180
            theta_shoulder = (theta_shoulder)*math.pi/180
            theta_elbow = (theta_elbow)*math.pi/180
            theta_claw1= (theta_claw1)*math.pi/180
            theta_claw2= (theta_claw2)*math.pi/180

            hello_str.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5']
            hello_str.position = [theta_base , theta_elbow , theta_shoulder, theta_claw1, theta_claw2]
            hello_str.velocity = []
            hello_str.effort = []
            pub.publish(hello_str)
        else:
            print ("Enter angles in range 0 to 180")
        
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
