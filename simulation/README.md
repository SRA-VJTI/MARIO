# Manipulator Simulation
* We will be creating a workspace in the `simulation/` folder and Testing out the Manipulator codes

# File Structure
    .
    └──src
        ├── simulation_gazebo       #package for running the Manipulator simulation in gazebo
            ├── launch              #folder containing the launch files
            ├── urdf                #folder containing the urdf files           
            ├── scripts             #folder containing the scripts
            ├── config              #folder containing the config.yaml file
            └── config              #folder containing the config.yaml file
        └── simulation_rviz         #package for running the Manipulator simulation in rviz
            ├── launch              #folder containing the launch files
            ├── urdf                #folder containing the urdf files           
            ├── scripts             #folder containing the scripts
            ├── config              #folder containing the config.yaml file
            └── config              #folder containing the config.yaml file


# Creating a Workspace
* For running the simulation, we first need to create a catkin workspace. Go to the simulation folder and type the following commands to do the same

1) Source ROS-Noetic and build the workspace 
```
source /opt/ros/noetic/setup.bash
catkin_make
source devel/setup.bash
```
2) Install the the drivers for ros-control

```
sudo apt-get install ros-noetic-ros-control ros-noetic-ros-controllers
```

Now you can run the simulations in Gazebo and RViz.

# Running the Simulation
* Follow [these steps](https://github.com/SRA-VJTI/ROS-Workshop-2.1/tree/master/simulation/simulation_gazebo) for running the simulation in Gazebo
* Follow [these steps](https://github.com/SRA-VJTI/ROS-Workshop-2.1/tree/master/simulation/simulation_rviz) for running the simulation in Rviz