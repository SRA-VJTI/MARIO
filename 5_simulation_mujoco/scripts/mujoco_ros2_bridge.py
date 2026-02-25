#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState
import mujoco
import mujoco.viewer
import numpy as np
import os
from ament_index_python.packages import get_package_share_directory
import threading

class MujocoRosBridge(Node):
    def __init__(self):
        super().__init__('mujoco_ros_bridge')
        
        package_share = get_package_share_directory('simulation_mujoco')
        model_path = os.path.join(package_share, 'models', 'manipulator.xml')
        
        self.model = mujoco.MjModel.from_xml_path(model_path)
        self.data = mujoco.MjData(self.model)
        self.viewer = None
        self.viewer_thread = None
        self.running = True
        self.joint_names = ['joint_1', 'joint_2', 'joint_3', 'joint_4', 'joint_5']
        
        self.joint_state_pub = self.create_publisher(JointState,'/joint_states',10)
        
        self.command_sub = self.create_subscription(Float64MultiArray,'/forward_position_controller/commands',self.command_callback,10)
        
        self.timer = self.create_timer(0.005, self.simulation_step)
        self.pub_timer = self.create_timer(0.02, self.publish_joint_states)
        self.target_positions = np.zeros(5) #starting postion is 0
        
        self.get_logger().info('Mujoco to ros bridge created')
        self.start_viewer()
    
    def start_viewer(self):
        def viewer_loop():
            self.viewer = mujoco.viewer.launch_passive(self.model, self.data)   # launching viewer
            while self.running and self.viewer.is_running():
                pass
        
        self.viewer_thread = threading.Thread(target=viewer_loop, daemon=True)
        self.viewer_thread.start()
    
    def command_callback(self, msg):
        if len(msg.data) >= 5:
            self.target_positions = np.array(msg.data[:5])
            self.get_logger().info(f'position command: {self.target_positions}')
    
    def simulation_step(self):
        self.data.ctrl[:5] = self.target_positions
        mujoco.mj_step(self.model, self.data)
        if self.viewer is not None and self.viewer.is_running():
            self.viewer.sync()
    
    def publish_joint_states(self):
        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.name = self.joint_names
        msg.position = self.data.qpos[:5].tolist()
        msg.velocity = self.data.qvel[:5].tolist()
        msg.effort = self.data.qfrc_actuator[:5].tolist()
        
        self.joint_state_pub.publish(msg)
    
    def shutdown(self):
        self.running = False
        if self.viewer is not None:
            self.viewer.close()

def main(args=None):
    rclpy.init(args=args)
    node = MujocoRosBridge()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.shutdown()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()