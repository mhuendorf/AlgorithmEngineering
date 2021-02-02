#include <representations/BasicSolution.hpp>
#include <representations/Point.hpp>

#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;


BasicSolution::BasicSolution(const Instance& instance) : Solution{instance}, placements{}, corners{} {}

BasicSolution& BasicSolution::operator=(const BasicSolution& other) {
    // TODO learn how to properly do this, this is most certainly wrong
    this->placements = other.placements;
    this->corners = other.corners;
    return *this;
}

int BasicSolution::size() const {
    return placements.size();
}

std::ostream& operator<<(std::ostream &ostream, const BasicSolution &solution) {

    ostream << solution.instance.size() << "\n";
    for (int i = 0; i < solution.instance.size(); ++i) {

        ostream << solution.instance.getPoint(i);

        std::map<int, Point::Rectangle>::const_iterator finder = solution.placements.find(i);
        if(solution.placements.end() != finder) {
            Point::Point2D rectCorner = std::get<0>(finder->second);
            ostream << "1 " << std::get<0>(rectCorner) << " " << std::get<1>(rectCorner);
        } else {
            ostream << "0 0 0";
        }
        ostream << std::endl;
    }
    return ostream;
}

void BasicSolution::printSolution(std::ostream &ostream) {
    ostream << *this << std::endl;
}

bool BasicSolution::isFeasible() const {

    auto it = placements.cbegin();
    while(it != placements.end()) {
        int idx = it->first;
        Point::Rectangle rect = it->second;
        const Point& p = instance.getPoint(idx);
        for(const Point::Ptr& other : p.getNeighbours()) {
            auto finder = placements.find((*other).getIdx());
            if(placements.end() != finder) {
                if(Point::checkCollision(rect, finder->second)) {
                    throw std::runtime_error("Points " + p.getName() + " and " + (*other).getName() + " overlap!");
                }
            }
        }
        it++;
    }

    // checked everything, never ran into a collision
    return true;
}

void BasicSolution::setLabel(int idx, Point::Corner corner) {

    placements.erase(idx);
    corners.erase(idx);

    if(corner == Point::Corner::NOT_PLACED) {
        return;
    }

    Point::Rectangle rect = instance.getPoint(idx).getCoordsForPlacement(corner);
    placements.insert(std::make_pair(idx, rect));
    corners.insert(std::make_pair(idx, corner));
}

void BasicSolution::resetLabel(int idx) {
    placements.erase(idx);
    corners.erase(idx);
}

bool BasicSolution::contains(int idx) const {
    auto finder = placements.find(idx);
    return placements.end() != finder;
}

Point::Corner BasicSolution::getCorner(int pointIdx) const {
    try {
        return corners.at(pointIdx);
    }  catch (const std::out_of_range &e) {
        return Point::Corner::NOT_PLACED;
    }
}

bool BasicSolution::checkCollision(const Point& p, Point::Corner placement, int otherIdx) const {

    if(!contains(otherIdx) || placement==Point::Corner::NOT_PLACED) {
        return false; // can't collide if the other one isn't even set
    }

    Point::Rectangle rect1 = p.getCoordsForPlacement(placement);
    Point::Rectangle rect2 = placements.find(otherIdx)->second;

    return Point::checkCollision(rect1, rect2);
}

BasicSolution::BasicSolution(const BasicSolution &basicSolution) : Solution(basicSolution) {
    this->placements = basicSolution.placements;
    this->corners = basicSolution.corners;
}
