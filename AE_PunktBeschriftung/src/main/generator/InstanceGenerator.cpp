#include <generator/InstanceGenerator.hpp>
#include <representations/Instance.hpp>

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

using namespace std;

Instance
InstanceGenerator::generateInstance(int numPoints, int fieldWidth, int fieldHeight, int maxBoxWidth, int maxBoxHeight,
                                    unsigned int seed) {
    if (numPoints > fieldHeight * fieldWidth) {
        throw std::exception();
    }
    if ((double) numPoints / (fieldHeight * fieldWidth) > 0.95) {
        cout << "Very crowded space... Instance generation might take a while" << endl;
    }
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
        bool doesExist;
        do {
            shared_ptr<Box> box = make_shared<Box>(rand() % maxBoxWidth + 1, rand() % maxBoxHeight + 1,
                                                   labels.at(rand() % labelSize));
            shared_ptr<PointWithLabel> point2D = make_shared<PointWithLabel>(rand() % fieldWidth + 1,
                                                                             rand() % fieldHeight + 1, move(box));
            bool isDuplicate = false;
            for (int j = 0; j < instance.size(); ++j) {
                shared_ptr<PointWithLabel> point = instance.getPoint(j);
                if (point2D->getX() == point->getX() && point2D->getY() == point->getY()) {
                    isDuplicate = true;
                    break;
                }
            }
            doesExist = isDuplicate;
            if (!isDuplicate) {
                instance + move(point2D);
            }
        } while (doesExist);
    }
    srand(1);
    return instance;
}
