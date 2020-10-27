//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_INSTANCEGENERATOR_HPP
#define UNTITLED_INSTANCEGENERATOR_HPP

#include <iostream>
#include "../representations/Instance.hpp"

class InstanceGenerator {

public:
    static Instance generateInstance(int numPoints,  int fieldWidth, int fieldHeight, int maxBoxWidth ,int maxBoxHeight, unsigned int seed);
};

#endif //UNTITLED_INSTANCEGENERATOR_HPP
