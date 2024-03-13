cmake_minimum_required(VERSION 3.13)
project(raylib_imgui_custom CXX)

# C++ standard
set(CMAKE_C_STANDARD C99)
set(CMAKE_CXX_STANDARD 11)

# Imgui sources
file(GLOB IMGUI_SOURCES "imgui-src-*/*.h" "imgui-src-*/*.cpp")
file(GLOB IMGUI_INCLUDE_DIRS "imgui-src-*")

# https://github.com/raylib-extras/rlImGui sources
file(GLOB RAYLIB_IMGUI_SOURCES "backend/*.h" "backend/*.cpp" "backend/*/*.h" "backend/*/*.cpp")
set(RAYLIB_IMGUI_SOURCES_INCLUDE_DIRS "backend" "extras")

# create the custom static library
add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCES} ${RAYLIB_IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_INCLUDE_DIRS} ${RAYLIB_IMGUI_SOURCES_INCLUDE_DIRS})

# Add compile definitions for ImGui
target_compile_definitions(${PROJECT_NAME} PRIVATE
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        IMGUI_DISABLE_OBSOLETE_KEYIO
)

# link raylib to it (it's an implicit requirement)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
