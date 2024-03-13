############## Raylib ############## (A simple library to make games)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied games
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE) # allow customizing the build
set(SUPPORT_FILEFORMAT_MOD OFF CACHE BOOL "" FORCE) # disable MOD file support
add_subdirectory(raylib-5.0 EXCLUDE_FROM_ALL)  # should be called before other "raylib-*" dependencies
############## Raylib ##############

############## Raylib-cpp ############## (C++ wrapper for Raylib)
add_subdirectory(raylib-cpp-5.0.1 EXCLUDE_FROM_ALL)
############## Raylib-cpp ##############

############## Raylib-imgui ############## (DearImGui wrapper for Raylib)
add_subdirectory(raylib-imgui-custom EXCLUDE_FROM_ALL)
############## Raylib-imgui ############## (DearImGui wrapper for Raylib)

target_link_libraries(${GameName} PRIVATE
        raylib
        raylib_cpp
        raylib_imgui_custom
)

