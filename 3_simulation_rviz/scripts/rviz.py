#!/usr/bin/python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from geometry_msgs.msg import TransformStamped
from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster
from std_msgs.msg import Header
from rclpy import qos
import math
import geometry_msgs.msg
import sys

# This function publishes the input angles of the user.
def talker():
    global node
    pub = node.create_publisher(JointState,'joint_states', qos_profile=qos.qos_profile_parameter_events)
    hello_str = JointState()
    hello_str.header = Header()
    hello_str.header.stamp = node.get_clock().now().to_msg()

    theta_base = float(input("{:22s}".format("Enter theta_base: ")))
    theta_shoulder = float(input("{:22s}".format("Enter theta_shoulder: ")))
    theta_elbow = float(input("{:22s}".format("Enter theta_elbow: ")))
    gripper_open = float(input("{:22s}".format("Enter Gripper Position(0 - close/ 1 - open): ")))
    #theta_claw2 = float(input("{:22s}".format("Enter theta_claw 2: ")))

    # theta must be in the range of 0 to 180 degree.
    if 0 <= theta_base <= 180.0 and 0 <= theta_shoulder <= 180.0 and 0 <= theta_elbow <= 180.0  : 
        theta_base = (theta_base)*math.pi/180
        theta_shoulder = (theta_shoulder)*math.pi/180
        theta_elbow = (theta_elbow)*math.pi/180
        if gripper_open:
            theta_gripper = 1.57
        else:
            theta_gripper = 0.0
        #theta_claw2= (theta_claw2)*math.pi/180

        hello_str.name = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5']
        hello_str.position = [theta_base , theta_shoulder , theta_elbow, theta_gripper, theta_gripper]
        hello_str.velocity = []
        hello_str.effort = []
        pub.publish(hello_str)
    else:
        print ("Enter angles in range!")
    

if __name__ == '__main__':

    rclpy.init(args=sys.argv)
    global node 
    node = rclpy.create_node('joint_state_pub')
    node.get_logger().info(' Enter your Angles ')
    node.create_timer(0.1, talker)
    rclpy.spin(node)
    rclpy.shutdown()
