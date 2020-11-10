#include <representations/Instance.hpp>

#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;

// Constructor: initializes points and reserves memory
Instance::Instance(int size) : points{}, labelled_points{} {
    reserve(size);
}

// reserves the needed space in memory for the vector of points and indices
void Instance::reserve(int num) {
    this->points.reserve(num);
    this->labelled_points.reserve(num);
}

// adds a point to this instance
void Instance::add(const Point& point) {
    this->points.push_back(point);
}

// sets the label for point at idx at the given Corner
void Instance::setLabel(int idx, Point::Corner corner) {

    // mark this point as labelled
    this->labelled_points.push_back(idx);
    this->points.at(idx).setPlacement(corner);

}

// prints every point of this instance to the stream
std::ostream& operator<<(std::ostream& ostream, const Instance& instance) {
    ostream << instance.size() << "\n";
    for (auto const &point : instance.points) {
        ostream << point << std::endl;
    }
    return ostream;
}

// returns the number of points
int Instance::size() const {
    return this->points.size();
}

// returns a reference to the point at a given index
const Point& Instance::getPoint(int idx) const {
    return points.at(idx);
}

std::vector<int>& Instance::getLabelledPoints() {
    return this->labelled_points;
}

int Instance::countLabelledPoints() const {
    return this->labelled_points.size();
}

bool Instance::isFeasible() const {
    for(std::size_t i = 0; i < labelled_points.size(); i++) {
        Point p = this->getPoint(labelled_points[i]);
        for(std::size_t j = i+1; j < labelled_points.size(); j++) {
            Point other = this->getPoint(labelled_points[j]);
        
            if(p.checkCollision(other)) {
                throw std::runtime_error("Points " + p.getName() + " and " + other.getName() + " overlap!");
            }
        }
    }
    return true;
}