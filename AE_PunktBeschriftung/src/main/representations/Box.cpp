#include <representations/Box.hpp>
#include <iostream>
#include <iomanip>

Box::Box(int width, int height, std::string label) {
    this->width = width;
    this->height = height;
    this->label = std::move(label);
}

std::ostream &operator<<(std::ostream &ostream, const Box &box) {
    return ostream << box.width << "\t" << box.height << "\t" << std::setw(40) << box.label;
}

int Box::getWidth() {
    return width;
}

int Box::getHeight() {
    return height;
}
