#include <iostream>
#include "representations/Box.hpp"
#include <representations/Point2D.hpp>
#include <representations/Instance.hpp>
#include <generator/InstanceGenerator.hpp>

int main() {
    Instance instance = InstanceGenerator::generateInstance(100, 50,  20, 10, 5, 10);
    std::cout << instance << std::endl;
    return 0;
}