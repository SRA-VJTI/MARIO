#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Vector3
import math
import inverse_kinematics_module

def inverse_kinematics_publisher():
	pub_array = rospy.Publisher('ros_arm_control', Vector3, queue_size=10) 
	rospy.init_node('inverse_kinematics_publisher', anonymous=True)
	rate = rospy.Rate(10)	#10hz
	msg = Vector3()			#ROS message type

	while not rospy.is_shutdown():
		#Input coordinates
		x = float(input("Enter x: "))
		y = float(input("Enter y: "))
		z = float(input("Enter z: "))

		angles = inverse_kinematics_module.compute_angles(x,y,z)
		
		#Print Joint angles
		print "*************************"
		print "{:15s}{:15s}{:15s}".format("theta_base", "theta_shoulder", "theta_elbow")
		print "{:<15f}{:<15f}{:<15f}".format(angles[0][0], angles[0][1], angles[0][2])
		print "{:<15f}{:<15f}{:<15f}".format(angles[1][0], angles[1][1], angles[1][2])

		#To handle redundancy
		#Always sending those angles having approach vector as (0, 0, 1)
		index = 0
		if angles[0][1] - angles[0][2] % math.pi == 0:
			index = 0
		elif angles[1][1] - angles[1][2] % math.pi == 0:
			index = 1

		msg.x = float(angles[index][0])
		msg.y = float(angles[index][1])
		msg.z = float(angles[index][2])
		
		rospy.loginfo(msg)
		pub_array.publish(msg)
		rate.sleep()

if __name__ == '__main__':
	try:
		inverse_kinematics_publisher()
	except rospy.ROSInterruptException:	
		pass