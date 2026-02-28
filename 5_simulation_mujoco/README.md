# Table of Contents
* [Steps to run the demo in Mujoco](#steps-to-run-the-demo-in-mujoco)
* [Steps For Running the Scripts in Mujoco](#steps-for-running-the-scripts-in-mujoco)

## Steps to run the demo in Mujoco
* Mujoco is a fast physics simulation engine. In this workshop we will be using Mujoco to simulate the Manipulator with a ROS2 bridge. For running the simulation just follow commands mentioned below

### Steps For Running the Scripts in Mujoco
We will be testing out 2 scripts (forward_kinematics.py, inverse_kinematics.py)


Source Ros2. Use following commands in your workspace :

```
source /opt/ros/humble/setup.bash
```
Now we build simulation_mujoco package using this command:

```
cd 5_simulation_mujoco/
colcon build
```
Now we source the workspace using following command :
```
source install/setup.bash
```
For running the scripts on mujoco, firstly launch mujoco using the command

```
ros2 launch simulation_mujoco mujoco_launch.py
```

After starting mujoco we will be testing out `forward_kinematics.py`.
Open a new terminal and navigate to your workspace. Now source the workspace and run forward_kinematics.py using following commands :

```
source install/setup.bash
ros2 run simulation_mujoco forward_kinematics.py
```
Similarly, you can test out the script for `inverse_kinematics.py`.
