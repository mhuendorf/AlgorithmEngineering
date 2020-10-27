#include <iostream>
#include "../../include/representations/Box.hpp"
#include "../../include/representations/Point2D.hpp"
#include "../../include/representations/Instance.hpp"
#include "../../include/generator/InstanceGenerator.hpp"

int main() {
    Instance instance = InstanceGenerator::generateInstance(100, 50,  20, 10 ,5, 10);
    std::cout << instance << std::endl;
    return 0;
}