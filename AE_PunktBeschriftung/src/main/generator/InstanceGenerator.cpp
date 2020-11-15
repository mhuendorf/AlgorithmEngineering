#include <generator/InstanceGenerator.hpp>
#include <representations/Instance.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

Instance
InstanceGenerator::generateInstance(int numPoints, int fieldWidth, int fieldHeight, int maxBoxWidth, int maxBoxHeight,
                                    unsigned int seed) {
    if (numPoints > fieldHeight * fieldWidth) {
        throw std::invalid_argument("Too many points for the given area!");
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
    Instance instance(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        bool doesExist;
        do {
            int x = rand() % maxBoxWidth + 1;
            int y = rand() % maxBoxHeight + 1;
            int width = rand() % fieldWidth + 1;
            int height = rand() % fieldHeight + 1;
            std::string label = labels.at(rand() % labelSize);

            Point point(i, x, y, width, height, label);

            bool isDuplicate = false;

            for (int j = 0; j < instance.size(); ++j) {
                Point existing = instance.getPoint(j);
                if (x == point.getX() && y == point.getY()) {
                    isDuplicate = true;
                    break;
                }
            }
            doesExist = isDuplicate;
            if (!isDuplicate) {
                instance.add(point);
            }
        } while (doesExist);
    }
    srand(1);
    return instance;
}
