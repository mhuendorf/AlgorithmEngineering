cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled src/tests/main.cpp src/main/InstanceGenerator.cpp include/generator/InstanceGenerator.hpp src/main/Instance.cpp include/representations/Instance.hpp src/main/Point2D.cpp include/representations/Point2D.hpp src/main/Box.cpp include/representations/Box.hpp src/main/Solver.cpp include/Solver.hpp src/main/Solution.cpp include/representations/Solution.hpp)