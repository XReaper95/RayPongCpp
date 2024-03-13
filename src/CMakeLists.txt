# Create a executable form the game sources
file(GLOB SOURCES "game/*.h" "game/*.cpp" main.cpp)
add_executable(${GameName} ${SOURCES})
