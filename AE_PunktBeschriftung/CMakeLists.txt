cmake_minimum_required(VERSION 3.3)
project(label_map)

# enable C++ compilation
option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

# assume build type release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# tell cmake to start searching from project source dir and find gurobi
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(GUROBI REQUIRED)

include_directories(${GUROBI_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

# adding this flag to get better valgrind output
# SET(GCC_COMPILE_FLAGS "-ggdb3")
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

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

target_compile_options(label_map PRIVATE -Wall)

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
        src/main/solver/TrivialSolver.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(falp PUBLIC include)

target_compile_options(falp PRIVATE -Wall -Werror)

# This will generate the popmusic solver:
add_executable(popmusic src/main/popmusic.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/FALPSolver.cpp
        src/main/solver/PopmusicSolver.cpp
        src/main/solver/Utils.cpp
        src/main/solver/TrivialSolver.cpp
        src/main/io/InstanceReader.cpp)

target_include_directories(popmusic PUBLIC include)

target_compile_options(popmusic PRIVATE -O3 -Wall -Werror)

# This will generate the popmusic solver with exact subproblem fixing:
#add_executable(popmusicexact src/main/popmusicexact.cpp
#        src/main/representations/Instance.cpp
#        src/main/representations/BasicSolution.cpp
#        src/main/representations/Solution.cpp
#        src/main/representations/Point.cpp
#        src/main/solver/FALPSolver.cpp
#        src/main/solver/PopmusicSolverExact.cpp
#        src/main/solver/Utils.cpp
#        src/main/solver/TrivialSolver.cpp
#        src/main/io/InstanceReader.cpp)

#target_include_directories(popmusicexact PUBLIC include)

#target_compile_options(popmusicexact PRIVATE -Wall -Werror)

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

target_compile_options(sa PRIVATE -Wall)

# This will generate the ILP solver:
add_executable(ilp src/main/exact.cpp
        src/main/representations/Instance.cpp
        src/main/representations/BasicSolution.cpp
        src/main/representations/Solution.cpp
        src/main/representations/Point.cpp
        src/main/solver/TrivialSolver.cpp
        src/main/solver/Utils.cpp
        src/main/io/InstanceReader.cpp
        src/main/solver/ExactSolver.cpp
        src/main/solver/CustomCallback.cpp)

if(CXX)
    set(CMAKE_CXX_STANDARD 17)
    target_link_libraries(ilp optimized ${GUROBI_CXX_LIBRARY} debug ${GUROBI_CXX_DEBUG_LIBRARY})
endif()

target_include_directories(ilp PUBLIC include)

target_link_libraries(ilp ${GUROBI_LIBRARY})

target_compile_options(ilp PRIVATE -Wall -Werror)