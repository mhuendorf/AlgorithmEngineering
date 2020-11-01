cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(test src/tests/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/PointWithLabel.cpp
        src/main/representations/Box.cpp
        src/main/representations/Point2D.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Rectangle.cpp
        src/main/representations/PlacedRectangle.cpp
)

target_include_directories(test PUBLIC include)

target_compile_options(test PRIVATE -Wall -Werror)
