#include <io/InstanceReader.hpp>
#include <representations/PointWithLabel.hpp>
#include <representations/Solution.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>

#include <vector>
using std::vector;

#include <string>
using std::string;



void readInstance(Instance& instance, const string& filename) {

    std::fstream file;

    // TODO check if successful
    file.open(filename, std::ios::in);

    if (file.is_open()) {
        string line;
        getline(file, line);
        // TODO make safe
        int numOfPoints = stoi(line);
        instance.reserve(numOfPoints);

        while(getline(file, line)) {
            instance + parseLine(line);
        }
        
        file.close();

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}

void readInstanceAndSolution(Instance& instance, Solution& solution, const string& filename) {

    std::fstream file;

    // TODO check if successful
    file.open(filename, std::ios::in);

    if (file.is_open()) {
        string line;
        getline(file, line);
        // TODO make safe
        int numOfPoints = stoi(line);
        instance.reserve(numOfPoints);
        solution.reserve(numOfPoints);

        int i = 0;
        while(getline(file, line)) {

            std::istringstream iss(line);
            vector<string> tokens{std::istream_iterator<std::string>{iss},
                            std::istream_iterator<std::string>{}};

            int x = stoi(tokens[0]);
            int y = stoi(tokens[1]);
            int width = stoi(tokens[2]);
            int height = stoi(tokens[3]);
            std::string name = tokens[4];

            bool isSet = stoi(tokens[5]);
            int upperLeftX = stoi(tokens[6]);
            int upperLeftY = stoi(tokens[7]);

            std::shared_ptr<Box> box = std::make_shared<Box>(width, height, name);

            instance + std::make_shared<PointWithLabel>(x, y, box);

            // TODO check validity
            if(isSet) {
                if(upperLeftX < x) {
                    if(upperLeftY == y) {
                        solution.placeLabel(i, Defs::TOP_RIGHT);
                    } else { // y is larger
                        solution.placeLabel(i, Defs::BOTTOM_RIGHT);
                    }
                } else {
                    if(upperLeftY == y) {
                        solution.placeLabel(i, Defs::TOP_LEFT);
                    } else {
                        solution.placeLabel(i, Defs::BOTTOM_LEFT);
                    }
                }
            }
            i++;
        }
        
        file.close();

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}

std::shared_ptr<PointWithLabel> parseLine(std::string const& line) {
    std::istringstream iss(line);
    vector<string> tokens{std::istream_iterator<std::string>{iss},
                      std::istream_iterator<std::string>{}};

    int x = stoi(tokens[0]);
    int y = stoi(tokens[1]);
    int width = stoi(tokens[2]);
    int height = stoi(tokens[3]);
    std::string name = tokens[4];

    std::shared_ptr<Box> box = std::make_shared<Box>(width, height, name);

    return std::make_shared<PointWithLabel>(x, y, box);
}
