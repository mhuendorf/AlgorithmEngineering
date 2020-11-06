cmake_minimum_required(VERSION 3.17)
project(labelpoints)

set(CMAKE_CXX_STANDARD 20)

add_executable(label_map src/main/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/PointWithLabel.cpp
        src/main/representations/Box.cpp
        src/main/representations/Point2D.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Rectangle.cpp
        src/main/representations/PlacedRectangle.cpp
        src/main/representations/Defs.cpp src/main/solver/TrivialSolver.cpp include/solver/TrivialSolver.hpp
        src/main/io/InstanceReader.cpp)

target_include_directories(label_map PUBLIC include)

target_compile_options(label_map PRIVATE -Wall -Werror)
