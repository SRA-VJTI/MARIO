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
    rospy.init_node('joint_state_pub' , anonymous=False)
    joint = [0.0, 0.0, 0.0]
    rate = rospy.Rate(10) # 10hz
    print("All the theta values to be entered in degrees")

    theta_base = float(input("{:22s}".format("Enter theta_base: ")))
    theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
    theta_elbow =  float(input("{:22s}".format("Enter theta_elbow: ")))

    while not rospy.is_shutdown():

        

        if -90.0 <= theta_base <= 90.0 and -72.0 <= theta_shoulder <= 72.0 and -107.0 <= theta_elbow <= 46.0: 
            joint[0] = (theta_base)*math.pi/180
            joint[1] = (theta_shoulder)*math.pi/180
            joint[2] = (theta_elbow)*math.pi/180

            rospy.loginfo("\ntheta_base = %f\ntheta_shoulder = %f\ntheta_elbow = %f", joint[0], joint[1], joint[2])
            Joint_1.publish(joint[0])
            Joint_2.publish(joint[1])
            Joint_3.publish(joint[2])
        else:
            print ("Enter angles in range -90 to 90")
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        rospy.signal_shutdown()
    except KeyboardInterrupt:
        rospy.signal_shutdown()
        