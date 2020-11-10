#include <io/InstanceReader.hpp>
#include <representations/Instance.hpp>
#include <representations/Point.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include <vector>
using std::vector;

#include <string>
using std::string;


Instance readInstance(const string& filename) {

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
        }

        Instance instance(numOfPoints);

        int counter = 0;
        while(getline(file, line)) {
            parseLine(instance, line);
            counter++;
        }
        if(counter != numOfPoints) {
            throw std::runtime_error("Actual number of points did not match expected number of points: Was " + std::to_string(counter) + " instead of " + std::to_string(numOfPoints));
        }
        
        file.close();

        return instance;

    } else {
        throw std::runtime_error("Error opening the file " + filename + "\n");
    }
}


int parsePositiveInteger(const string& line) {
    int result = stoi(line);
    if(result < 1) throw std::runtime_error("Expected a positive integer, got " + line + " instead.");
    return result;
}

void parseLine(Instance& instance, const std::string& line) {

    // unpacking the scanned line into a vector of strings
    std::istringstream iss(line);
    vector<string> tokens{std::istream_iterator<std::string>{iss},
                      std::istream_iterator<std::string>{}};

    // asserting proper size - greater than 5 is okay because there might be a solution in there as well
    if(tokens.size() != 5 && tokens.size() != 8) {
        throw std::runtime_error("Expected 5 or 8 arguments per line, got " + std::to_string(tokens.size()) + " instead for line < " + line + " >.");
    }

    // parsing arguments to ints if needed
    try {

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

        Point point(x, y, width, height, name);
        instance.add(point);

        if(tokens.size() == 8) {
            int isSet = stoi(tokens[5]);

            if(isSet != 0 && isSet != 1) throw std::runtime_error("Could not parse boolean, expected 0 or 1 but was " + std::to_string(isSet));

            int upperLeftX = stoi(tokens[6]);
            int upperLeftY = stoi(tokens[7]);

            if(isSet) {
                checkBoxConsistency(x, y, width, height, upperLeftX, upperLeftY);

                Point::Corner corner = parseCornerPlacement(x, y, upperLeftX, upperLeftY);

                instance.setLabel(instance.size()-1, corner);
            }
        }


    } catch(const std::exception& e) {
        throw std::runtime_error("Could not parse line < " + line + " >, where 4 ints and a string were expected.\n" + e.what());
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

Point::Corner parseCornerPlacement(int x, int y, int upperLeftX, int upperLeftY) {
    if(upperLeftX < x) {
        if(upperLeftY == y) {
            return Point::TOP_RIGHT;
        } else { // y is larger
            return Point::BOTTOM_RIGHT;
        }
    } else {
        if(upperLeftY == y) {
            return Point::TOP_LEFT;
        } else {
            return Point::BOTTOM_LEFT;
        }
    }
}