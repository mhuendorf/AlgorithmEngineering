#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/ExactSolver.hpp>
#include <io/InstanceReader.hpp>

#include <iostream>
#include <solver/Utils.hpp>

int main(int argc, char* argv[]) {
    Instance instance;
    BasicSolution sol(instance);
    readInstance("../res/tinyInstance.txt", instance, sol);

    TrivialSolver trivial;
    //ExactSolver solver(trivial);
    //BasicSolution solution = solver.solve(instance);

    std::vector<int> values;
    values.push_back(getLabelIdx(0, Point::Corner::BOTTOM_LEFT));
    values.push_back(getLabelIdx(1, Point::Corner::BOTTOM_LEFT));
    values.push_back(getLabelIdx(2, Point::Corner::BOTTOM_RIGHT));
    values.push_back(getLabelIdx(3, Point::Corner::TOP_RIGHT));
    values.push_back(getLabelIdx(4, Point::Corner::TOP_LEFT));
    BasicSolution solution = trivial.solve(instance, values);

    std::cout << solution << solution.isFeasible() << std::endl;
    //std::cout << solution << solution.isFeasible() << std::endl;

    return 0;
} 