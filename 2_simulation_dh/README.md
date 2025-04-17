# DH Parameters Simulation

## Overview

Denavit-Hartenberg (DH) parameters are a systematic method for defining the reference frames of robotic manipulators. This project demonstrates DH parameters for a 3-Degree of Freedom (DOF) robot arm.

### What are DH Parameters?
DH parameters describe the orientation and position of each joint in a robotic manipulator using four parameters:
- Link length
- Link twist
- Link offset
- Joint angle

These parameters are crucial for:
- Simplifying forward kinematics calculations
- Enabling inverse kinematics solutions
- Standardizing frame transformations

## Visualization Demo in RViz

This demo provides a visual representation of the DH parameters using RViz, ROS 2's 3D visualization tool.

### Prerequisites
- ROS 2 installed and configured
- Working ROS 2 workspace (`ros2_ws`)
- MARIO repository cloned

### Installation Steps

1. Copy the simulation files to your ROS 2 workspace if not already present:
   ```bash
   cp -r ~/MARIO/2_simulation_dh ~/ros2_ws/src
   ```

2. Navigate to your ROS 2 workspace:
   ```bash
   cd ~/ros2_ws
   ```

3. Build the packages:
   ```bash
   colcon build
   ```

4. Source the workspace:
   ```bash
   source install/setup.bash
   ```

### Running the Simulation

Launch the visualization:
```bash
ros2 launch simulation_dh dh_transformation_visualization.launch.py
```

## Demo

<p align="center">
   <img src="assets/dh_simulation_visulization.gif" width="800" height="500" alt="DH Parameters Visualization">
</p>

## Notes
- Make sure all dependencies are properly installed
- Ensure your ROS 2 environment is correctly sourced
- The visualization helps in understanding the spatial relationships between different joints of the robot
