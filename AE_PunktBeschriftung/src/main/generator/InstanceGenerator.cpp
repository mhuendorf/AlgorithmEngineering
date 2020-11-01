//
// Created by Marcel Hündorf on 26.10.20.
//

#include <generator/InstanceGenerator.hpp>
#include <representations/Instance.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

using namespace std;
Instance
InstanceGenerator::generateInstance(int numPoints,  int fieldWidth, int fieldHeight, int maxBoxWidth, int maxBoxHeight,
                                    unsigned int seed) {
    ifstream infile("../res/city_names.txt");
    vector<string> labels;

    string city;
    while (getline(infile, city)) {
        labels.push_back(city);
    }
    infile.close();

    srand(seed);

    int labelSize = labels.size();
    Instance instance;
    for (int i = 0; i < numPoints; ++i) {
        shared_ptr<Box> box = make_shared<Box>(rand()%maxBoxWidth+1, rand()%maxBoxHeight+1, labels.at(rand()%labelSize));
        shared_ptr<PointWithLabel> point2D = make_shared<PointWithLabel>(rand() % fieldWidth + 1, rand() % fieldHeight + 1, move(box));
        instance + move(point2D);
    }
    srand(1);
    return instance;
}
