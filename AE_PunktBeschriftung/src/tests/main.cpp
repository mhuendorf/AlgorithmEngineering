#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/ExactSolver.hpp>
#include <io/InstanceReader.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    Instance instance;
    BasicSolution sol(instance);
    readInstance("../res/paris.txt", instance, sol);

    TrivialSolver trivial;
    ExactSolver solver(trivial);
    BasicSolution solution = solver.solve(instance);

    std::cout << solution << solution.isFeasible() << std::endl;
    //std::cout << solution << solution.isFeasible() << std::endl;

    return 0;
} 