//
// Created by Marcel Hündorf on 26.10.20.
//

#include "InstanceGenerator.hpp"
#include "../representations/Instance.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mach/mach_types.h>
#include <sstream>
#include <string>

Instance
InstanceGenerator::generateInstance(int numPoints,  int fieldWidth, int fieldHeight, int maxBoxWidth ,int maxBoxHeight,
                                    unsigned int seed) {
    std::ifstream infile("../res/city_names.txt");
    std::vector<std::string> labels;

    std::string city;
    while (std::getline(infile, city)) {
        labels.push_back(city);
    }

    srand(seed);

    int labelSize = labels.size();
    Instance instance = Instance();
    for (int i = 0; i < numPoints; ++i) {
        Box* box = new Box(rand()%maxBoxWidth+1, rand()%fieldHeight+1, labels.at(rand()%labelSize));
        Point2D point2D(rand()%fieldWidth+1, rand()%fieldHeight+1, box);
        instance + point2D;
    }

    srand(1);
    return instance;
}
