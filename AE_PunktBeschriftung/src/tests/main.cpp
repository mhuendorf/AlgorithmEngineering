#include <iostream>
#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/Solution.hpp>
#include <solver/TrivialSolver.hpp>

using namespace std;

int main() {
    int numPoints = 10000;
    Instance instance = InstanceGenerator::generateInstance(numPoints, 500000, 500000, 10, 5, 10);
    cout << instance << endl;

    TrivialSolver trivialSolver;
    Solution sol = *trivialSolver.solve(instance);
    cout << (sol.isFeasible() ? "true" : "false") << endl;
    cout << sol;
    return 0;
}