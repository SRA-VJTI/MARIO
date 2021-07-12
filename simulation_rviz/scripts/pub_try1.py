#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import JointState
from std_msgs.msg import Header

def talker():
    pub = rospy.Publisher('joint_states', JointState, queue_size=10)
    rospy.init_node('joint_state_bhau' , anonymous=False)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        hello_str = JointState()
        hello_str.header = Header()
        hello_str.header.stamp = rospy.Time.now()
        theta_base = float(input("{:22s}".format("Enter theta_base: ")))
        theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
        theta_elbow = float(input("{:22s}".format("Enter theta_elbow: ")))
        hello_str.name = ['joint_1', 'joint_2', 'joint_3']
        hello_str.position = [theta_base , theta_elbow , theta_shoulder]
        hello_str.velocity = []
        hello_str.effort = []
        pub.publish(hello_str)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
