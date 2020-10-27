#include <iostream>
#include "../main/representations/Box.hpp"
#include "../main/representations/Point2D.hpp"
#include "../main/representations/Instance.hpp"
#include "../main/generator/InstanceGenerator.hpp"

int main() {
    Instance instance = InstanceGenerator::generateInstance(100, 50,  20, 10, 5, 10);
    std::cout << instance << std::endl;
    return 0;
}