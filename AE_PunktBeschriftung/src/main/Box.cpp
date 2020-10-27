//
// Created by Marcel Hündorf on 26.10.20.
//

#include <representations/Box.hpp>
#include <iostream>
#include <iomanip>

Box::Box(int width, int height, std::string label) {
    this->width = width;
    this->height = height;
    this->label = std::move(label);
}

std::ostream &operator<<(std::ostream& ostream, const Box& box) {
    return ostream << std::setw(6) << box.width << std::setw(6) << box.height << std::setw(40) << box.label;
}