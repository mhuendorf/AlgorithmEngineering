cmake_minimum_required(VERSION 3.17)
project(label_map)

set(CMAKE_CXX_STANDARD 20)

# This will generate the final project = the best working solver
add_executable(label_map src/main/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp 
        src/main/io/InstanceReader.cpp
        src/main/representations/Solution.cpp src/main/solver/SimulatedAnnealing.cpp include/solver/SimulatedAnnealing.hpp src/main/representations/SimulatedAnnealingSolution.cpp include/representations/SimulatedAnnealingSolution.hpp)

target_include_directories(label_map PUBLIC include)

target_compile_options(label_map PRIVATE -Wall -Werror)

# This is only needed for our experiments: unique executable for every solver. (Can be removed when we hand this in.)

# This will generate the trivial solver:
add_executable(trivial src/main/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp 
        src/main/io/InstanceReader.cpp
        src/main/representations/Solution.cpp)

target_include_directories(trivial PUBLIC include)

target_compile_options(trivial PRIVATE -Wall -Werror)
