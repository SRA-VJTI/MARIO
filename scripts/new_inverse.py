#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import numpy as np
import math 

# Variables
d0 = 2.5
a1 = 12.0
d3 = 9.5

def compute_angles(x, y, z):

	theta0 = math.atan2(y, x)

	domain = ((x*x + y*y + ((z-d0))*((z-d0))) - a1*a1 - d3*d3) / (2*a1*d3)
	# print(((x*x + y*y + ((z-d0))*((z-d0))) - a1*a1 - d3*d3))
	# print(2*a1*d3)

	if domain<=1 and domain>=-1:
		
		theta2 = math.asin(domain)
		theta2_possible = math.pi - theta2
		if theta0 != 90:
			theta1 = math.asin((((z-d0))*((a1 + d3*math.sin(theta2))) + d3*math.cos(theta2)*x/math.cos(theta0)) / (x*x + y*y + ((z-d0))*((z-d0))))
			theta1_possible = math.asin((((z-d0))*((a1 + d3*math.sin(theta2_possible))) + d3*math.cos(theta2_possible)*x/math.cos(theta0)) / (x*x + y*y + ((z-d0))*((z-d0))))
			# print((((z-d0))*((a1 + d3*math.sin(theta2))) + d3*math.cos(theta2)*x/math.cos(theta0)))
			# print((x*x + y*y + ((z-d0))*((z-d0))))
		elif theta != 0:
			theta1 = math.asin(((z-d0)*(a1 + d3*math.sin(theta2)) + d3*math.cos(theta2)*y/math.sin(theta0)) / (x*x + y*y + ((z-d0))*((z-d0))))
			theta1_possible = math.asin(((z-d0)*(a1 + d3*math.sin(theta2_possible)) + d3*math.cos(theta2_possible)*y/math.sin(theta0)) / (x*x + y*y + ((z-d0))*((z-d0))))

	else:

		print("point is not in range due to constrain in link length")
		return [None, None, None]

	result = [[math.degrees(theta0), math.degrees(theta1), math.degrees(theta2)], [math.degrees(theta0), math.degrees(theta1_possible), math.degrees(theta2_possible)]]

	return result

def talker():
		pub_array = rospy.Publisher('ros_arm_control', String, queue_size=10) 
		rospy.init_node('talker', anonymous=True)
		rate = rospy.Rate(10)	#10hz
		msg = String()

		while not rospy.is_shutdown():
			x = float(input("Enter x "))
			y = float(input("Enter y "))
			z = float(input("Enter z "))

			angles = compute_angles(x,y,z)

			print(angles[0][0], angles[0][1], angles[0][2])
			print("\tOR")	
			print(angles[1][0], angles[1][1], angles[1][2])

			angle_str = ""

			for i in angles[0]:
				angle_str = angle_str + str(i) + " "

			msg.data = angle_str
			print(msg.data)
			
			rospy.loginfo(msg)
			pub_array.publish(msg)
			msg.data = ""
			rate.sleep()

if __name__ == '__main__':
	try:
		talker()
		
	except rospy.ROSInterruptException:	
		pass