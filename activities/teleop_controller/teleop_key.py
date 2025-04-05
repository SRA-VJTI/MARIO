#!/usr/bin/python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
import sys
import termios
import tty
import threading
from rclpy import qos
import math

msg = """
Robot Arm Teleop Controller
---------------------------
Moving around:
   q    w    e
   a    s    d
   z    x    c

w/s : increase/decrease base angle
a/d : increase/decrease shoulder angle
q/e : increase/decrease elbow angle
z/c : open/close gripper
x : home position

CTRL-C to quit
"""

# Initial joint angles
joint_angles = [0.0, 0.0, 0.0, 0.0, 0.0]  # [base, shoulder, elbow, gripper1, gripper2]
angle_step = 0.1  # Radians

def getKey(settings):
    tty.setraw(sys.stdin.fileno())
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def saveTerminalSettings():
    return termios.tcgetattr(sys.stdin)

class TeleopNode(Node):
    def __init__(self):
        super().__init__('teleop_key')
        self.publisher = self.create_publisher(
            Float64MultiArray,
            '/forward_position_controller/commands',
            qos_profile=qos.qos_profile_parameter_events
        )
        self.joint_msg = Float64MultiArray()
        self.joint_msg.data = joint_angles

    def publish_joints(self):
        try:
            self.joint_msg.data = [float(angle) for angle in joint_angles]
            self.publisher.publish(self.joint_msg)
        except Exception as e:
            self.get_logger().error(f'Failed to publish joint angles: {str(e)}')

def main():
    global joint_angles
    settings = saveTerminalSettings()
    rclpy.init()
    teleop_node = TeleopNode()

    print(msg)

    def update_loop():
        while True:
            try:
                rclpy.spin_once(teleop_node)
            except Exception as e:
                print(f"Spin error: {e}")

    # Start the ROS update thread
    update_thread = threading.Thread(target=update_loop)
    update_thread.daemon = True
    update_thread.start()

    try:
        while True:
            key = getKey(settings)

            if key == '\x03':
                break


            previous_angles = joint_angles.copy()

            try:
                # Base joint control (0 to 180 degrees = 0 to π radians)
                if key == 'w':
                    if joint_angles[0] < math.pi:
                        joint_angles[0] = min(joint_angles[0] + angle_step, math.pi)
                elif key == 's':
                    if joint_angles[0] > 0:
                        joint_angles[0] = max(joint_angles[0] - angle_step, 0.0)

                # Shoulder joint control (0 to 180 degrees = 0 to π radians)
                elif key == 'a':
                    if joint_angles[1] < math.pi:
                        joint_angles[1] = min(joint_angles[1] + angle_step, math.pi)
                elif key == 'd':
                    if joint_angles[1] > 0:
                        joint_angles[1] = max(joint_angles[1] - angle_step, 0.0)

                # Elbow joint control (0 to 180 degrees = 0 to π radians)
                elif key == 'q':
                    if joint_angles[2] < math.pi:
                        joint_angles[2] = min(joint_angles[2] + angle_step, math.pi)
                elif key == 'e':
                    if joint_angles[2] > 0:
                        joint_angles[2] = max(joint_angles[2] - angle_step, 0.0)

                # Gripper control
                elif key == 'z':  # Open gripper
                    joint_angles[3] = 0.8
                    joint_angles[4] = 0.8
                elif key == 'c':  # Close gripper
                    joint_angles[3] = 0.0
                    joint_angles[4] = 0.0

                # Home position
                elif key == 'x':
                    joint_angles[:] = [0.0, 0.0, 0.0, 0.0, 0.0]

                # Only publish if angles have changed and are valid
                if joint_angles != previous_angles:
                    teleop_node.publish_joints()
                    print(f"\rCurrent joint angles: {[round(angle, 3) for angle in joint_angles]}", end='', flush=True)

            except Exception as e:
                # Revert to previous angles if there's an error
                joint_angles = previous_angles
                print(f"\nError: {e}")

    except Exception as e:
        print(f"\nError: {e}")

    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        teleop_node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
