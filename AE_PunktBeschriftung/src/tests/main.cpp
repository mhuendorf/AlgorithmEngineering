#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/Solution.hpp>
#include <solver/TrivialSolver.hpp>
#include <io/InstanceReader.hpp>

int test() {
    int numPoints = 10000;
    Instance instance = InstanceGenerator::generateInstance(numPoints, 500000, 500000, 10, 5, 10);
    cout << instance << endl;

    Instance test;
    readInstance(test, "../res/tinyInstance.txt");
    cout << test << endl;

    Instance test2;
    Solution testSol(test2);
    readInstanceAndSolution(test2, testSol, "../res/tinyInstanceAndSolution.txt");

    cout << test2 << endl;
    cout << testSol << endl;

    // int numPoints = 100;
    // Instance instance = InstanceGenerator::generateInstance(numPoints, 50, 50, 10, 5, 10);
    // cout << instance << endl;

    // TrivialSolver trivialSolver;
    // Solution sol = *trivialSolver.solve(instance);
    // cout << (sol.isFeasible() ? "true" : "false") << endl;
    // cout << sol;
    return 0;
}