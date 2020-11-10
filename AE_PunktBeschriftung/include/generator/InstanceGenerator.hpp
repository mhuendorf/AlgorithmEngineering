#pragma once 

#include <representations/Instance.hpp>

#include <iostream>

class InstanceGenerator {

public:
    static Instance generateInstance(int numPoints, int fieldWidth, int fieldHeight, int maxBoxWidth, int maxBoxHeight,
                                     unsigned int seed);
};

