cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS "${EXTRA_COMPONENT_DIRS}" "./../components/micro_ros_espidf_component" "../components/sra-board-component")
# Append the directories to the EXTRA_COMPONENT_DIRS variable
list(APPEND EXTRA_COMPONENT_DIRS "./../components/micro_ros_espidf_component" "../components/sra-board-component")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32_servo_subs)

# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)


