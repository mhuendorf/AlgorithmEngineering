#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/Solution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/FALPSolver.hpp>
#include <io/InstanceReader.hpp>

int main(int argc, char* argv[]) {
    Instance instance;
    Solution sol(instance);
    readInstance("../res/tinyInstance.txt", instance, sol);

    FALPSolver solver;
    Solution solution = solver.solve(instance);


    std::cout << solution << std::endl;

    return 0;
}