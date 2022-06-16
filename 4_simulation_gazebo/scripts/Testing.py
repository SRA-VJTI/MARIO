#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64
import math

def talker():

    #Initialiizing Publishers
    Joint_1 = rospy.Publisher('/manipulator/joint_1_controller/command',Float64, queue_size=10)
    Joint_2 = rospy.Publisher('/manipulator/joint_2_controller/command',Float64, queue_size=10)
    Joint_3 = rospy.Publisher('/manipulator/joint_3_controller/command',Float64, queue_size=10)
    Joint_4 = rospy.Publisher('/manipulator/joint_4_controller/command',Float64, queue_size=10)
    rospy.init_node('joint_state_pub' , anonymous=False)
    joint = [0.0, 0.0, 0.0, 0.0]
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():

        print("All the theta values to be entered in degrees")

        theta_base = float(input("{:22s}".format("Enter theta_base: ")))
        theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
        theta_elbow =  float(input("{:22s}".format("Enter theta_elbow: ")))
        theta_claw =  float(input("{:22s}".format("Enter theta_claw: ")))


        if 0.0 <= theta_base <= 180.0 and 0.0 <= theta_shoulder <= 180.0 and 0.0 <= theta_elbow <= 180.0 and 0.0 <= theta_claw <= 180.0: 
            joint[0] = (theta_base)*math.pi/180
            joint[1] = (theta_shoulder)*math.pi/180
            joint[2] = (theta_elbow)*math.pi/180
            joint[3] = (theta_claw)*math.pi/180

            rospy.loginfo("\ntheta_base = %f\ntheta_shoulder = %f\ntheta_elbow = %f\ntheta_claw = %f", joint[0], joint[1], joint[2], joint[3])
            Joint_1.publish(joint[0])
            Joint_2.publish(joint[1])
            Joint_3.publish(joint[2])
            Joint_4.publish(joint[3])

        else:
            print ("Enter angles in range 0 to 180")
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass