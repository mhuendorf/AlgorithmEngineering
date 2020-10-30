//
// Created by Marcel Hündorf on 26.10.20.
//

#include <representations/Instance.hpp>
#include <representations/Point2D.hpp>

#include <iostream>
#include <memory>
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <fstream>
#include <sstream>
#include <iterator>

Instance::Instance() {
}

Instance::Instance(string filename) : points{} {

    std::fstream file;

    file.open(filename, std::ios::in);

    if (file.is_open()) {
        string line;
        getline(file, line);

        points.reserve(stoi(line));

        while(getline(file, line)) {
            *this + (parseLine(line));
        }
        
        file.close();

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}

void Instance::operator+(std::unique_ptr<Point2D> point2D) {
    this->points.push_back(std::move(point2D));
}

std::ostream &operator<<(std::ostream& ostream, const Instance& instance) {
    for (auto const& point : instance.points) {
        ostream << *point << std::endl;
    }
    return ostream;
}

std::unique_ptr<Point2D> parseLine(std::string const& line) {
    std::istringstream iss(line);
    vector<string> tokens{std::istream_iterator<std::string>{iss},
                      std::istream_iterator<std::string>{}};

    int x = stoi(tokens[0]);
    int y = stoi(tokens[1]);
    int width = stoi(tokens[2]);
    int height = stoi(tokens[3]);
    std::string name = tokens[4];

    std::unique_ptr<Box> box = std::make_unique<Box>(width, height, name);

    return std::make_unique<Point2D>(x, y, std::move(box));
}