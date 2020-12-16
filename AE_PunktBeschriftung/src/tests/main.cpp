#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/ExactSolver.hpp>
#include <io/InstanceReader.hpp>

int main(int argc, char* argv[]) {
    Instance instance;
    BasicSolution sol(instance);
    readInstance("../res/tinyInstance.txt", instance, sol);

    ExactSolver solver;
    BasicSolution solution = solver.solve(instance);


    std::cout << solution << solution.isFeasible() << std::endl;

    return 0;
}