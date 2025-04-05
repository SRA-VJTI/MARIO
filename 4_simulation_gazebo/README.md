# Table of Contents
* [Steps to run the demo in Gazebo](#steps-to-run-the-demo-in-gazebo)
* [Steps For Running the Scripts in Gazebo](#steps-for-running-the-scripts-in-gazebo)

## Steps to run the demo in Gazebo
* Gazebo is the simulation tool that is used by ROS. It has a lot of Applications. In this workshop we will be using ROS to simulate the Manipulator. For the running the simulation just follow commands mentioned below.
* If you have not installed the joint_state_publishers and ros_control for ros-noetic, follow the commands given [here](https://github.com/SRA-VJTI/MARIO/tree/master/4_simulation_gazebo)

*  Run the launch file

Make sure you have sourced your workspace before running this command.
```
  ros2 launch simulation_gazebo basic_gazebo.launch.py
```

To source your workspace follow the steps menstioned below.
<p align="center">
  <img src="../assets/gazebo.png" width="800"/>
</p>


### Steps For Running the Scripts in Gazebo
We will be testing out 2 scripts (forward_kinematics.py, inverse_kinematics.py).

Firstly copy the 4_simulation_gazebo folder to src folder in your workspace using command (in fresh terminal) :

```
cp -r MARIO/4_simulation_gazebo ros2_ws/src
```
Now source Ros2. Use following commands in your workspace :

```
source /opt/ros/humble/setup.bash
```
Now we build simulation_gazebo package using this command:

```
colcon build
```
Now we source the workspace using following command :
```
source install/setup.bash
```
For running the scripts on gazebo, firstly launch gazebo world using the command

```
ros2 launch simulation_gazebo basic_gazebo.launch.py
```

After starting gazebo we will be testing out `forward kinematics.py`.
Open a fresh terminal and navigate to your workspace. Now source the workspace and run forward_kinematics.py using following commands :

```
source install/setup.bash
ros2 run simulation_gazebo forward_kinematics.py
```
Similarly, you can test out the script for `inverse_kinematics.py`.
