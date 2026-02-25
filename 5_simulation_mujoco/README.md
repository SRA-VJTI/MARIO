## Steps to run the demo in Mujoco

### Build the package

Make sure you have sourced ROS 2 before building:
```
source /opt/ros/humble/setup.bash
```

Navigate to the mujoco folder and build:
```
cd 5_simulation_mujoco/
colcon build
```

### Run the simulation

Source the workspace and launch the Mujoco bridge:
```
source install/setup.bash
ros2 launch simulation_mujoco mujoco_launch.py
```

With the simulation running, open a new terminal and source the workspace:
```
source install/setup.bash
```

### Forward Kinematics

Enter joint angles and the arm moves to that position.
```
ros2 run simulation_mujoco forward_kinematics.py
```

### Inverse Kinematics

Enter an XYZ coordinate and the arm moves to that position:
```
ros2 run simulation_mujoco inverse_kinematics.py
```
