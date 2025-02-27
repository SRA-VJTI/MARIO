cmake_minimum_required(VERSION 3.8)
project(simulation_gazebo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)
find_package(xacro REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(ros2_control REQUIRED)
find_package(ign_ros2_control REQUIRED)
find_package(joint_state_broadcaster REQUIRED)
find_package(joint_trajectory_controller REQUIRED)
find_package(robot_state_publisher REQUIRED)
find_package(ros_ign_gazebo REQUIRED)

install(PROGRAMS
  scripts/forward_kinematics.py scripts/inverse_kinematics.py scripts/forward_kinematics_module.py scripts/inverse_kinematics_module.py
  DESTINATION lib/${PROJECT_NAME}
)
install(
  DIRECTORY config launch meshes rviz scripts urdf
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
