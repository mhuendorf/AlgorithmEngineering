cmake_minimum_required(VERSION 3.17)
project(label_map)

set(CMAKE_CXX_STANDARD 20)

add_executable(label_map src/main/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp 
        src/main/solver/FALPSolver.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(label_map PUBLIC include)

target_compile_options(label_map PRIVATE -Wall -Werror)

add_executable(test src/tests/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp 
        src/main/solver/FALPSolver.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(test PUBLIC include)

target_compile_options(test PRIVATE -Wall -Werror)