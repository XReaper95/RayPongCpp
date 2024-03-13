#### WIP

# Tell Emscripten to build an example.html file.
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

# Required linker flags for using Raylib with Emscripten
target_link_options(${PROJECT_NAME} PRIVATE
        -sEXPORTED_FUNCTIONS=['_main','_malloc']
        -sEXPORTED_RUNTIME_METHODS=ccall
        -sUSE_GLFW=3
)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file resources@resources")
