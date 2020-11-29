#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/Solution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/FALPSolver.hpp>
#include <solver/PopmusicSolver.hpp>
#include <io/InstanceReader.hpp>

int main(int argc, char* argv[]) {
    Instance instance;
    Solution sol(instance);
    readInstance("../res/tinyInstance.txt", instance, sol);

    PopmusicSolver solver(instance);
    Solution solution = solver.solve(instance);


    std::cout << solution << solution.isFeasible() << std::endl;

    return 0;
}