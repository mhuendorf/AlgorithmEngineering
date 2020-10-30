//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_INSTANCE_HPP
#define UNTITLED_INSTANCE_HPP

#include <stack>
#include <vector>
#include "Point2D.hpp"
#include <memory>

class Instance {
private:
    std::vector< std::unique_ptr<Point2D> > points;
    friend std::ostream& operator<<(std::ostream& ostream, const Instance& instance);

public:
    Instance();

    Instance(std::string filename);

    void operator+(std::unique_ptr<Point2D> point2D);
};

std::unique_ptr<Point2D> parseLine(std::string const& line);

#endif //UNTITLED_INSTANCE_HPP
