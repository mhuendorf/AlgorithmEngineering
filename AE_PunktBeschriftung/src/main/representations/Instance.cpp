#include <representations/Instance.hpp>

#include <iostream>
#include <memory>
#include <string>
using std::string;

#include <vector>
using std::vector;


Instance::Instance() : points{} {};

// Constructor: initializes points and reserves memory
Instance::Instance(int size) : points{} {
    reserve(size);
}

// reserves the needed space in memory for the vector of points and indices
void Instance::reserve(int num) {
    this->points.reserve(num);
}

// adds a point to this instance
void Instance::add(const Point::Ptr& point) {

    for(Point::Ptr& p : points) {

        if((*point).couldCollide(*p)) {
            // note: This is a horrible idea and should be fixed, but was the simplest way of avoiding memory leaks
            (*p).addNeighbour( point.get() );
            (*point).addNeighbour( p.get() );
        }
    }
    this->points.push_back(point);
}

void Instance::showPoints() {
    for(const Point::Ptr& p : points) {
        std::cout << "Point " << (*p).getName() << " hat Adresse " << &(*p) << std::endl;

        for(const Point* ptr : (*p).getNeighbours()) {
            std::cout << "Neighbour " << (*ptr).getName() << " hat Adresse " << &(*ptr) << std::endl;
        }
    }
}

//prints every point of this instance to the stream
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
    if(0 <= idx && idx < size()) {
        return *points.at(idx);
    } else {
        throw std::invalid_argument("Index must be between 0 and size of instance!");
    }
}

const std::vector<Point::Ptr>& Instance::getPoints() const {
    return points;
}