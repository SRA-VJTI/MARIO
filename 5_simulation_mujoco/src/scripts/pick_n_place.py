#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState
import forward_kinematics_module
import math
import tkinter as tk
from tkinter import ttk
import threading

class SimpleGUIController(Node):
    def __init__(self):
        super().__init__('simple_gui_controller')
        
        self.target_x = -12.0
        self.target_y = 8.0
        self.target_z = 2.5
        
        self.d = [10, 0, 0, 13]
        self.alpha = [math.pi/2, 0, math.pi/2, 0]
        self.a = [0, 6, 0, 0]

        self.joint_pub = self.create_publisher(
            Float64MultiArray,
            '/forward_position_controller/commands',
            10
        )

        self.joint_sub = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_callback,
            10
        )

        self.current_position = [0.0, 0.0, 0.0]

        self.theta_base = 90.0
        self.theta_shoulder = 90.0
        self.theta_elbow = 90.0

        self.get_logger().info('GUI Created')

        self.gui_thread = threading.Thread(target=self.create_gui, daemon=True)
        self.gui_thread.start()
    
    def joint_state_callback(self, msg):
        if len(msg.position) >= 3:
            theta = [
                math.degrees(msg.position[0]),
                math.degrees(msg.position[1]),
                math.degrees(msg.position[2]),
                0
            ]
            
            transform = forward_kinematics_module.compute_coordinates(
                theta, self.d, self.alpha, self.a
            )
            
            self.current_position = [
                transform[0, 3],
                transform[1, 3],
                transform[2, 3]
            ]
            
            error = math.sqrt(
                (self.current_position[0] - self.target_x)**2 +
                (self.current_position[1] - self.target_y)**2 +
                (self.current_position[2] - self.target_z)**2
            )
            
            print(f"Current: X={self.current_position[0]:.2f}, Y={self.current_position[1]:.2f}, Z={self.current_position[2]:.2f} | Error={error:.2f} cm")
    
    def create_gui(self):
        root = tk.Tk()
        root.title("Joint Angle Control")
        root.geometry("600x400")

        tk.Label(root, text="Joint 1 - Base (0-180°)", font=('Arial', 11)).pack(pady=10)
        self.slider1 = tk.Scale(root, from_=0, to=180, orient='horizontal',length=500, command=self.update_angles)
        self.slider1.set(90)
        self.slider1.pack()

        tk.Label(root, text="Joint 2 - Shoulder (0-180°)", font=('Arial', 11)).pack(pady=10)
        self.slider2 = tk.Scale(root, from_=0, to=180, orient='horizontal',length=500, command=self.update_angles)
        self.slider2.set(90)
        self.slider2.pack()

        tk.Label(root, text="Joint 3 - Elbow (0-180°)", font=('Arial', 11)).pack(pady=10)
        self.slider3 = tk.Scale(root, from_=0, to=180, orient='horizontal',length=500, command=self.update_angles)
        self.slider3.set(90)
        self.slider3.pack()

        button_frame = tk.Frame(root)
        button_frame.pack(pady=20)
        
        tk.Button(button_frame, text="Open Gripper", command=self.open_gripper,width=15, height=2).pack(side='left', padx=10)
        tk.Button(button_frame, text="Close Gripper", command=self.close_gripper,width=15, height=2).pack(side='left', padx=10)
        
        root.mainloop()
    
    def update_angles(self, val):
        self.theta_base = float(self.slider1.get())
        self.theta_shoulder = float(self.slider2.get())
        self.theta_elbow = float(self.slider3.get())
        self.send_command(0.8)
    
    def open_gripper(self):
        self.send_command(0.8)
    
    def close_gripper(self):
        self.send_command(0.0)
    
    def send_command(self, gripper):
        msg = Float64MultiArray()
        msg.data = [
            self.theta_base * math.pi / 180,
            self.theta_shoulder * math.pi / 180,
            self.theta_elbow * math.pi / 180,
            gripper,
            gripper
        ]
        self.joint_pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = SimpleGUIController()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()