#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64
import math
import inverse_kinematics_module

def inverse_kinematics_publisher():
    Joint_1 = rospy.Publisher("manipulator/joint_1_controller/command",Float64,queue_size = 10)
    Joint_2 = rospy.Publisher("manipulator/joint_2_controller/command",Float64,queue_size = 10)
    Joint_3 = rospy.Publisher("manipulator/joint_3_controller/command",Float64,queue_size = 10)
    rospy.init_node('inverse_kinematics_publisher', anonymous=True)
    rate = rospy.Rate(10)	#10hz
    joint = [0.0, 0.0, 0.0]

    while not rospy.is_shutdown():
        #Input coordinates
        x = float(input("Enter x: "))
        y = float(input("Enter y: "))
        z = float(input("Enter z: "))

        angle = inverse_kinematics_module.compute_angles(x,y,z)

		# Sending, if angles are in range of servos i.e 0 to 180
        index = -1
        count = 0
        print(angle)
        if angle[0][0] != None and angle[0][1] != None and angle[0][2] != None:
            if 0.0 <= int(angle[0][0]) <= 180.0 and 0.0 <= int(angle[0][1]) <= 180.0 and 0.0 <= int(angle[0][2]) <= 180.0:
                # angles_found = True
                index = 0
                count += 1

            if 0.0 <= int(angle[1][0]) <= 180.0 and 0.0 <= int(angle[1][1]) <= 180.0 and 0.0 <= int(angle[1][2]) <= 180.0:
                # angles_found = True
                index = 1
                count += 1

        if index != -1:

            #Print Joint angles
            print ("*************************")
            print ("{:15s}{:15s}{:15s}".format("theta_base", "theta_shoulder", "theta_elbow"))
            print ("{:<15f}{:<15f}{:<15f}".format(angle[0][0], angle[0][1], angle[0][2]))
            print ("{:<15f}{:<15f}{:<15f}".format(angle[1][0], angle[1][1], angle[1][2]))
            # Send angles
            if(count == 2):
                # To handle redundancy
                # Always sending those angles having approach vector as (0, 0, 1)
                # Condition for that is theta_shoulder + theta_elbow should be odd multiple of 180
                if (int(angle[0][1]) + int(angle[0][2])) % (2 * 180) != 0 and (int(angle[0][1]) + int(angle[0][2])) % 180 == 0:
                    index = 0

                elif (int(angle[1][1]) + int(angle[1][2])) % (2 * 180) != 0 and (int(angle[1][1]) + int(angle[1][2])) % 180 == 0:
                    index = 1

            #Converting Degrees to Radians
            joint[0] = (int(angle[index][0]))*math.pi/180
            joint[1] = (int(angle[index][1]))*math.pi/180
            joint[2] = (int(angle[index][2]))*math.pi/180
            rospy.loginfo("\ntheta_base = %f\ntheta_shoulder = %f\ntheta_elbow = %f", joint[0], joint[1], joint[2])

            #Publishing Joint angle Values
            Joint_1.publish(joint[0])
            Joint_2.publish(joint[1])
            Joint_3.publish(joint[2])
            print ("=========================\n")

        else:
			# Print error message
            print ("Angles not sent due to constraints")
            print ("Please enter points in range")

        rate.sleep()

if __name__ == '__main__':
    try:
        inverse_kinematics_publisher()
    except rospy.ROSInterruptException:	
        pass