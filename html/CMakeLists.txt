# Tell Emscripten to build an example.html file.
set_target_properties(${GameName} PROPERTIES SUFFIX ".html")

# Required linker flags for using Raylib with Emscripten
target_link_options(${GameName} PRIVATE
        -sUSE_GLFW=3
        -sASSERTIONS=1
        -sWASM=1
        -sASYNCIFY
        -sGL_ENABLE_GET_PROC_ADDRESS=1
        -sEXPORTED_FUNCTIONS=['_main','_malloc']
        -sEXPORTED_RUNTIME_METHODS=ccall
        --preload-file ../resources
)
