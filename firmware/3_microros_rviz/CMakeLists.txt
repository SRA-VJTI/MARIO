cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS "${EXTRA_COMPONENT_DIRS}" "./../components")
# Append the directories to the EXTRA_COMPONENT_DIRS variable

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(microros_rviz)


# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
