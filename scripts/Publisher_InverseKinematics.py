#!/usr/bin/env python
import rospy
from std_msgs.msg import String	
# from sra.msg import custom_array
import numpy as np
import math 

pi_by_2 = math.pi/2
pi = math.pi

##Variables
link1_length = 2.5
correction_factor = 0
link_length_1 = 12
link_length_2 = 9.5


def compute_angles(x,y,z):
	theta1 = math.atan2(y,x) 
	
	if theta1==0 :
		w1 = x/math.cos(theta1)

	elif  theta1 == (pi_by_2):
		w1 = y/math.sin(theta1)

	else:
		w1 = x/math.cos(theta1)

	w2 = z - link1_length
	domain=(w1**2 + w2**2 - link_length_2**2 -link_length_1**2)/(2*link_length_2*link_length_1)
	#print("domain=",domain)
	if domain <= 1 and domain >= -1 :
		theta3 = math.acos(domain)
		theta3_neg= -theta3


	    
		theta2_a= math.atan2((w2*(link_length_1+link_length_2*math.cos(theta3)))-(w1*link_length_2*math.sin(theta3)),(w1*(link_length_1+link_length_2*math.cos(theta3)))+link_length_2*w2*math.sin(theta3))
		theta2_b=math.atan2(((w2*(link_length_1+link_length_2*math.cos(theta3_neg)))-w1*link_length_2*math.sin(theta3_neg)),(w1*(link_length_1+link_length_2*math.cos(theta3_neg))+link_length_2*w2*math.sin(theta3_neg)))
		
		#print("theta2_a==",theta2_a)
		#print("theta2_b==",theta2_b)
		if theta2_a < 0 and theta2_b < 0 :
			print("Point in not in range due to servo constrain ")
			theta1=0; theta2=0;theta3=0
			return theta1,theta2,theta3+90
		else :
			theta2=max(theta2_a,theta2_b)
			if theta2==theta2_b :
				theta3=theta3_neg 




			theta1 = float((math.degrees(theta1)))
			theta2 = float((math.degrees(theta2)))
			theta3 = float((math.degrees(theta3)))
			
			# if theta3<-90 or theta3>90:
			# 	print("point is not in range due to constrin in 3rd servo")
			# 	theta1=0 ; theta2=0 ; theta3=0

			
			return theta1, theta2, theta3+90

	else :
		print("point is not in range due to constrain in link length")
		theta1=0;theta2=0;theta3=0
		return	theta1,theta2,theta3+90
	

def talker():
		pub = rospy.Publisher('ros_arm_control',String, queue_size=10)
		rospy.init_node('talker', anonymous=True)
		rate = rospy.Rate(10) # 10hz
		msg = String()
		while not rospy.is_shutdown():
			x = input("Enter x ")
			y = input("Enter y ")
			z = input("Enter z ")
			# hello_str = "hello world %s" % rospy.get_time()
			angle_str = ""

			for i in compute_angles(x,y,z):
				angle_str = angle_str + str(i) + " "

			msg.data = angle_str

			print(msg.data)
			rospy.loginfo(msg)
			pub.publish(msg)
			msg.data = ""
			rate.sleep()
   
if __name__ == '__main__':
	try:
		talker()
		
	except rospy.ROSInterruptException:	
		pass

##Compute angles from provided co-ordinates




	
