cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled src/tests/main.cpp src/main/generator/InstanceGenerator.cpp src/main/generator/InstanceGenerator.hpp src/main/representations/Instance.cpp src/main/representations/Instance.hpp src/main/representations/Point2D.cpp src/main/representations/Point2D.hpp src/main/representations/Box.cpp src/main/representations/Box.hpp)

target_compile_options(untitled PRIVATE -Wall -Werror)
