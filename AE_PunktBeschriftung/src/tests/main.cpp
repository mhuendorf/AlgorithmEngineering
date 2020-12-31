#include <iostream>
using std::cout;
using std::endl;

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/ExactSolver.hpp>
#include <io/InstanceReader.hpp>

int main(int argc, char* argv[]) {
    Instance instance;
    BasicSolution sol(instance);
    readInstance("../res/100_10000_9.txt