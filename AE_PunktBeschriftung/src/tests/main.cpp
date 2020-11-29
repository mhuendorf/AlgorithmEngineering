#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/TrivialSolver.hpp>
#include <io/InstanceReader.hpp>

int test() {
    int numPoints = 10000;
    Instance instance = InstanceGenerator::generateInstance(numPoints, 500000, 500000, 10, 5, 10);
    cout << instance << endl;

    Instance test;
    BasicSolution sol(test);
    readInstance("../res/tinyInstance.txt", test, sol);
    cout << test << endl;

    Instance test2;
    BasicSolution testSol(test2);
    readInstance("../res/tinyInstanceAndSolution.txt", test2, testSol);

    cout << test2 << endl;
    testSol.printSolution(cout);
    
    // int numPoints = 100;
    // Instance instance = InstanceGenerator::generateInstance(numPoints, 50, 50, 10, 5, 10);
    // cout << instance << endl;

    // TrivialSolver trivialSolver;
    // Solution sol = *trivialSolver.solve(instance);
    // cout << (sol.isFeasible() ? "true" : "false") << endl;
    // cout << sol;
    return 0;
}