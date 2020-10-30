cmake_minimum_required(VERSION 3.17)
project(labelpoints)

set(CMAKE_CXX_STANDARD 20)

add_executable(labelpoints src/tests/main.cpp 
        src/main/generator/InstanceGenerator.cpp 
        src/main/representations/Instance.cpp 
        src/main/representations/Point2D.cpp 
        src/main/representations/Box.cpp)

target_include_directories(labelpoints PUBLIC include)

target_compile_options(labelpoints PRIVATE -Wall -Werror)
