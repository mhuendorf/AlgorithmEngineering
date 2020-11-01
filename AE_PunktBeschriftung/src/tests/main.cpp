#include <iostream>
#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>
#include <representations/Solution.hpp>

using namespace std;
int main() {
    Instance instance = InstanceGenerator::generateInstance(100, 50,  20, 10, 5, 10);
    cout << instance << endl;

    Solution sol(instance);
    sol.placeLabel(0, Defs::TOP_LEFT);
    sol.placeLabel(1, Defs::TOP_LEFT);

    return 0;
}