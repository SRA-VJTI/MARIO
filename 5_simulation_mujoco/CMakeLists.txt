cmake_minimum_required(VERSION 3.8)
project(simulation_mujoco)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(robot_state_publisher REQUIRED)

install(PROGRAMS
  scripts/mujoco_ros2_bridge.py
  scripts/forward_kinematics.py
  scripts/inverse_kinematics.py
  scripts/forward_kinematics_module.py
  scripts/inverse_kinematics_module.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  models
  meshes
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()