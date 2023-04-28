# Drawing a circle using Turtlesim in ROS

To run this script, you first need to create a new package called `turtle_circle` in the `catkin_ws/src` directory. You can do this by running the following commands in your terminal:

```bash
cd ~/catkin_ws/src
catkin_create_pkg turtle_circle rospy geometry_msgs
cd ..
catkin_make
```

Once you have created the package, you can copy the code below into a new file called `draw_circle.py` inside the `src` directory of your `turtle_circle` package. You can then run the script by navigating to your catkin_ws directory in your terminal and running the following command:

```bash
source devel/setup.bash
rosrun turtle_circle draw_circle.py
```

## Explanation

The script imports the `rospy` library and the `Twist` message type from the `geometry_msgs` package. It then defines a function called `draw_circle()` that will be used to control the turtle.

The `draw_circle()` function creates a publisher to the `turtle1/cmd_vel` topic, which is used to control the turtle's movement. It initializes the node with the name `turtle_circle` and sets the linear and angular velocities of the turtle to 1.0. It then sets the rate at which the turtle will move to 10 Hz.

The while loop in the function repeatedly publishes the `move_cmd` message to the `turtle1/cmd_vel` topic until the script is interrupted.

The `if __name__ == '__main__'`: block at the end of the script calls the `draw_circle()` function and handles any exceptions that may occur. The try-except block at the end of the script catches any `rospy.ROSInterruptException`, like a CTRL + C, that might be raised during the execution of the `draw_circle()` function. If such an exception is raised, the pass statement simply allows the script to exit gracefully without causing an error.

# Assignment

Draw a spiral using the turtle in turtlesim. You can use the `draw_spiral.py` script as a starting point.

## Hints

Increase the linear velocity and angular velocity of the turtle to make the spiral bigger.