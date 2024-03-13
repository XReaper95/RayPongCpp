cmake_minimum_required(VERSION 3.13)
project(RayPongCpp)

# the name of the game executable, used as the reference target
set(GameName "RayPongCpp")

# set the CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# C++ configurations
set(CMAKE_CXX_STANDARD 20) # standard
include(CompilerFlags) # C++ compiler configurations

# main game project
add_subdirectory(src)

# external dependencies
add_subdirectory(vendor)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    add_subdirectory("html")
endif()

