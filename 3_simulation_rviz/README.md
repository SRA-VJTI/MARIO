## Steps to run the demo in RViz
Introduction to RViz 2:

RViz 2 is a powerful 3D visualization tool provided by the Robot Operating System (ROS) 2 ecosystem. It serves as an essential component for roboticists, engineers, and researchers to visualize and interact with robot models, sensor data, and other important information in a simulated or real-world environment. RViz 2 offers a user-friendly interface with a wide range of features tailored to support the development, debugging, and testing of robotic systems.Here , along we can visualize the URDF of manipulator on Rviz using command line as well as GUI to give input.

If you have not installed the joint_state_publishers and ros_control for ros-noetic, follow the commands given [here](https://github.com/SRA-VJTI/MARIO/tree/master/3_simulation_rviz)

* Remember : Whenever you are using ros commands in another terminal , make sure you  source the ros commands:
```
source install/setup.bash
```


*  Run the launch file
```
  ros2 launch simulation_rviz display.launch.py
```


<p align="center">
  <img src="../assets/launch1.png" width="500"/>
</p>


   *  If you come across this error
Could not find the GUI, install the 'joint_state_publisher_gui' package
   *  Install  using
sudo apt install ros-<your_version_of_ros>-joint-state-publisher-gui
   * Install all the packages required in the same way if needed.

 ----------------------------------------------------------------------

*  Once you are done with the visualisation with gui , Ctrl+ c to stop this .


*  For command line input

```
ros2 launch simulation_rviz rviz.launch.py
```
* To give input angles from command line
```
ros2 run simulation_rviz rviz.py
```

*you can use your this command to view the topics actively published . This will show if the values are published to the toppic we want to.
```
ros2 topic list
```
*To observe the published data in another terminal
```
ros2 topic echo
```
Then initially set all values to zero , to get the default position of the manipulator .
After this you can now check for different values.

As you give the input in the terminal , you can observe how the manipulator moved according to your input values of angles between links.
