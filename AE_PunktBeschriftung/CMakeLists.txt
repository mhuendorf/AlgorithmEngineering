cmake_minimum_required(VERSION 3.17)
project(label_map)

set(CMAKE_CXX_STANDARD 20)

# This will generate the final project = the best working solver
add_executable(label_map src/main/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp 
        src/main/solver/FALPSolver.cpp
        src/main/solver/PopmusicSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp
        src/main/io/InstanceReader.cpp
        src/main/representations/Solution.cpp
        src/main/solver/SimulatedAnnealing.cpp
        src/main/representations/SimulatedAnnealingSolution.cpp)

target_include_directories(label_map PUBLIC include)

target_compile_options(label_map PRIVATE -Wall -Werror)

# This will be removed later, is only here for development
add_executable(test src/tests/main.cpp
        src/main/generator/InstanceGenerator.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp
        src/main/solver/FALPSolver.cpp
        src/main/solver/PopmusicSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(test PUBLIC include)

target_compile_options(test PRIVATE -Wall -Werror)


# This is only needed for our experiments: unique executable for every solver. (Can be removed when we hand this in.)

# This will generate the trivial solver:
add_executable(trivial src/main/trivial.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(trivial PUBLIC include)

target_compile_options(trivial PRIVATE -Wall -Werror)

# This will generate the falp solver:
add_executable(falp src/main/falp.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/FALPSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(falp PUBLIC include)

target_compile_options(falp PRIVATE -Wall -Werror)

# This will generate the falp solver:
add_executable(popmusic src/main/popmusic.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/FALPSolver.cpp
        src/main/solver/PopmusicSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(popmusic PUBLIC include)

target_compile_options(popmusic PRIVATE -Wall -Werror)

# This will generate the sa solver:
add_executable(sa src/main/sa.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/representations/SimulatedAnnealingSolution.cpp
        src/main/io/InstanceReader.cpp
        src/main/solver/SimulatedAnnealing.cpp)

target_include_directories(sa PUBLIC include)

target_compile_options(sa PRIVATE -Wall -Werror -v)
