cmake_minimum_required(VERSION 3.10.2)
project(Khoren)

set(CMAKE_CXX_STANDARD 17)

add_executable(Khoren main.cpp)
add_subdirectory(lib/sleepy-discord)
target_link_libraries(Khoren sleepy-discord)
install(TARGETS Khoren DESTINATION bin)