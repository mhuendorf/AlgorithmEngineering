#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/ExactSolver.hpp>
#include <io/InstanceReader.hpp>

#include <iostream>
#include <queue>
#include <solver/Utils.hpp>

int main(int argc, char* argv[]) {

    auto compare = [](std::tuple<int, double> a, std::tuple<int, double> b) { return std::get<1>(a) < std::get<1>(b); };
    std::priority_queue<std::tuple<int, double>, std::vector<std::tuple<int, double>>, decltype(compare)> suggestionQ(compare);

    suggestionQ.push(std::make_pair(2,0.9));
    suggestionQ.push(std::make_pair(1,0.95));
    suggestionQ.push(std::make_pair(4,0.5));
    suggestionQ.push(std::make_pair(3,0.7));

    while(!suggestionQ.empty()) {
        int sug = std::get<0>(suggestionQ.top());
        suggestionQ.pop();
        std::cout << sug << std::endl;
    }

    // Instance instance;
    // BasicSolution sol(instance);
    // //readInstance("../res/benchmark/vardens_100_10000_8.txt", instance, sol);
    // readInstance("/home/thomas/AE/Benchmark_Instances_CLPP/benchmark_instances/literature_instances/RandomRect/RandomRect_0750_01", instance, sol);
    // TrivialSolver trivial;

    // BasicSolution baseline = trivial.solve(instance);
    // std::cout << "Baseline: " << baseline.size() << std::endl;
    // ExactSolver solver;
    // BasicSolution solution = solver.solve(instance);

    // // std::vector<int> values;
    // // values.push_back(getLabelIdx(0, Point::Corner::BOTTOM_LEFT));
    // // values.push_back(getLabelIdx(1, Point::Corner::BOTTOM_LEFT));
    // // values.push_back(getLabelIdx(2, Point::Corner::BOTTOM_RIGHT));
    // // values.push_back(getLabelIdx(3, Point::Corner::TOP_RIGHT));
    // // values.push_back(getLabelIdx(4, Point::Corner::TOP_LEFT));
    // // BasicSolution solution = trivial.solve(instance, values);

    // // std::cout << solution << std::endl;
    // std::cout << "Solver delivered a solution, let's check it out!" << std::endl;
    // std::cout << "Solution is feasible: " << solution.isFeasible() << std::endl;
    // std::cout << "Solution has size: " << solution.size() << std::endl;

    return 0;
} 