#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Vector3
import math
import inverse_kinematics_module

def inverse_kinematics_publisher():
	publisher_ik = rospy.Publisher('ros_arm_control', Vector3, queue_size=10) 
	rospy.init_node('inverse_kinematics_publisher', anonymous=True)
	rate = rospy.Rate(10)	#10hz
	calculated_angle = Vector3()			#ROS message type

	while not rospy.is_shutdown():
		#Input coordinates
		x = float(input("Enter x: "))
		y = float(input("Enter y: "))
		z = float(input("Enter z: "))

		angle = inverse_kinematics_module.compute_angles(x,y,z)
		
		#Print Joint angles
		print "*************************"
		print "{:15s}{:15s}{:15s}".format("theta_base", "theta_shoulder", "theta_elbow")
		print "{:<15f}{:<15f}{:<15f}".format(angle[0][0], angle[0][1], angle[0][2])
		print "{:<15f}{:<15f}{:<15f}".format(angle[1][0], angle[1][1], angle[1][2])

		# Sending, if angles are in range of servos i.e 0 to 180
		index = -1
		count = 0
		if 0.0 <= int(angle[0][0]) <= 180.0 and 0.0 <= int(angle[0][1]) <= 180.0 and 0.0 <= int(angle[0][2]) <= 180.0:
			# angles_found = True
			index = 0
			count += 1

		if 0.0 <= int(angle[1][0]) <= 180.0 and 0.0 <= int(angle[1][1]) <= 180.0 and 0.0 <= int(angle[1][2]) <= 180.0:
			# angles_found = True
			index = 1
			count += 1

		if index != -1:
			# Send angles
			print count

			if(count == 2):
				# To handle redundancy
				# Always sending those angles having approach vector as (0, 0, 1)
				# Condition for that is theta_shoulder + theta_elbow should be odd multiple of 180
				if (int(angle[0][1]) + int(angle[0][2])) % (2 * 180) != 0 and (int(angle[0][1]) + int(angle[0][2])) % 180 == 0:
					index = 0

				elif (int(angle[1][1]) + int(angle[1][2])) % (2 * 180) != 0 and (int(angle[1][1]) + int(angle[1	][2])) % 180 == 0:
					index = 1
		
			calculated_angle.x = int(angle[index][0])
			calculated_angle.y = int(angle[index][1])
			calculated_angle.z = int(angle[index][2])
			rospy.loginfo(calculated_angle)
			publisher_ik.publish(calculated_angle)
		else:
			# Print error message
			print "Angles not sent due to constrains"
			print "Please enter points in range"

		rate.sleep()

if __name__ == '__main__':
	try:
		inverse_kinematics_publisher()
	except rospy.ROSInterruptException:	
		pass