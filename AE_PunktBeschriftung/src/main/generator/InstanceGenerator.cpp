//
// Created by Marcel Hündorf on 26.10.20.
//

#include <generator/InstanceGenerator.hpp>
#include <representations/Instance.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <mach/mach_types.h>
#include <sstream>
#include <string>
#include <memory>
#include <utility>

Instance
InstanceGenerator::generateInstance(int numPoints,  int fieldWidth, int fieldHeight, int maxBoxWidth, int maxBoxHeight,
                                    unsigned int seed) {
    std::ifstream infile("../res/city_names.txt");
    std::vector<std::string> labels;

    std::string city;
    while (std::getline(infile, city)) {
        labels.push_back(city);
    }

    srand(seed);

    int labelSize = labels.size();
    Instance instance;
    for (int i = 0; i < numPoints; ++i) {
        std::unique_ptr<Box> box = std::make_unique<Box>(rand()%maxBoxWidth+1, rand()%fieldHeight+1, labels.at(rand()%labelSize));
        std::unique_ptr<Point2D> point2D = std::make_unique<Point2D>(rand()%fieldWidth+1, rand()%fieldHeight+1, std::move(box));
        instance + std::move(point2D);
    }

    srand(1);
    return instance;
}
