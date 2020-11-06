#include <io/InstanceReader.hpp>
#include <representations/PointWithLabel.hpp>
#include <representations/Solution.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>
#include <stdexcept>

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
        int numOfPoints;
        try {
            numOfPoints = parsePositiveInteger(line);
        } catch (const std::exception& e) {
            throw std::runtime_error("Could not parse number of points for file " + filename + "\n" + e.what());
            return;
        }

        instance.reserve(numOfPoints);
        int counter = 0;
        while(getline(file, line)) {
            instance + parseLine(line);
            counter++;
        }
        if(counter != numOfPoints) {
            throw std::runtime_error("Actual number of points did not match expected number of points: Was " + std::to_string(counter) + " instead of " + std::to_string(numOfPoints));
        }
        
        file.close();

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}

int parsePositiveInteger(const string& line) {
    int result = stoi(line);
    if(result < 1) throw std::runtime_error("Expected a positive integer, got " + line + " instead.");
    return result;
}

std::shared_ptr<PointWithLabel> parseLine(std::string const& line) {

    // unpacking the scanned line into a vector of strings
    std::istringstream iss(line);
    vector<string> tokens{std::istream_iterator<std::string>{iss},
                      std::istream_iterator<std::string>{}};

    // asserting proper size - greater than 5 is okay because there might be a solution in there as well
    if(tokens.size() < 5) {
        throw std::runtime_error("Expected at least 5 arguments per line, got " + std::to_string(tokens.size()) + " instead for line < " + line + " >.");
    }

    // parsing arguments to ints if needed
    try {

        int x = stoi(tokens[0]);
        int y = stoi(tokens[1]);
        int width = parsePositiveInteger(tokens[2]);
        int height = parsePositiveInteger(tokens[3]);
        std::string name = tokens[4];

        // creating and returning a PointWithLabel
        std::shared_ptr<Box> box = std::make_shared<Box>(width, height, name);
        return std::make_shared<PointWithLabel>(x, y, box);

    } catch(const std::exception& e) {
        throw std::runtime_error("Could not parse line < " + line + " >, where 4 ints and a string were expected.\n" + e.what());
    }    
}

// Reads an instance and a solution from a given file
void readInstanceAndSolution(Instance& instance, Solution& solution, const string& filename) {

    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.is_open()) {
        string line;
        getline(file, line);

        int numOfPoints;
        try {
            numOfPoints = parsePositiveInteger(line);
        } catch (const std::exception& e) {
            throw std::runtime_error("Could not parse number of points for file " + filename + "\n" + e.what());
            return;
        }

        // reserving enough space in the vectors to avoid copying
        instance.reserve(numOfPoints);
        solution.reserve(numOfPoints);

        int i = 0;
        while(getline(file, line)) {

            std::istringstream iss(line);
            vector<string> tokens{std::istream_iterator<std::string>{iss},
                            std::istream_iterator<std::string>{}};

            if(tokens.size() != 8) {
                throw std::runtime_error("Expected exactly 8 arguments per line, got " + std::to_string(tokens.size()) + " instead for line < " + line + " >.");
            }

            int x = stoi(tokens[0]);
            int y = stoi(tokens[1]);
            int width;
            int height;
            try {
                width = parsePositiveInteger(tokens[2]);
                height = parsePositiveInteger(tokens[3]);
            } catch(const std::exception& e) {
                throw std::runtime_error("Could not parse label-box of point " + tokens[4] + "\n" + e.what());
            }
            std::string name = tokens[4];
            int isSet = stoi(tokens[5]);
            if(isSet != 0 && isSet != 1) throw std::runtime_error("Could not parse boolean in line " + std::to_string(i) + ", expected 0 or 1 but was " + std::to_string(isSet));
            int upperLeftX = stoi(tokens[6]);
            int upperLeftY = stoi(tokens[7]);
            if(isSet) {
                checkBoxConsistency(x, y, width, height, upperLeftX, upperLeftY);
            }
            std::shared_ptr<Box> box = std::make_shared<Box>(width, height, name);

            instance + std::make_shared<PointWithLabel>(x, y, box);

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

        if(i != numOfPoints) {
            throw std::runtime_error("Actual number of points did not match expected number of points: Was " + std::to_string(i) + " instead of " + std::to_string(numOfPoints));
        }
        
        file.close();

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}

// throws an exception if the position of a box is inconsistent with a point and the size of the label
void checkBoxConsistency(int x, int y, int width, int height, int upperLeftX, int upperLeftY) {
    if( !(x == upperLeftX || x - width == upperLeftX) // if x-coordinate does not make sense
        || !(y == upperLeftY || y + height == upperLeftY)) { // of if y-coordinate does not make sense
            throw std::runtime_error("Label positioning is inconsistent: point at ("+std::to_string(x)+","+std::to_string(y)+")" 
            + " with label size (" + std::to_string(width) + "," + std::to_string(height) + ")"
            + " cannot have upper left label corner in position (" + std::to_string(upperLeftX) + "," + std::to_string(upperLeftY) + ")" );
        }
}