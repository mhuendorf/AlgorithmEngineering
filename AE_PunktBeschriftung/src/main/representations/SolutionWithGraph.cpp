#include <representations/SolutionWithGraph.hpp>
#include <representations/Point.hpp>

#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;


SolutionWithGraph::SolutionWithGraph(Instance &instance) : Solution(instance), placements{} {}


int SolutionWithGraph::size() const {
    return placements.size();
}

bool SolutionWithGraph::isFeasible() const {

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

void SolutionWithGraph::setLabel(int idx, Point::Corner corner) {

    Point::Rectangle rect = instance.getPoint(idx).getCoordsForPlacement(corner);
    placements.insert(std::make_pair(idx, rect));

}

bool SolutionWithGraph::contains(int idx) const {
    auto finder = placements.find(idx);
    return placements.end() != finder;
}

bool SolutionWithGraph::checkCollision(const Point& p, Point::Corner placement, int otherIdx) const {

    if(!contains(otherIdx)) {
        return false; // can't collide if the other one isn't even set
    }

    Point::Rectangle rect1 = p.getCoordsForPlacement(placement);
    Point::Rectangle rect2 = placements.find(otherIdx)->second;

    return Point::checkCollision(rect1, rect2);
}

std::ostream &SolutionWithGraph::operator<<(std::ostream &ostream) {
    ostream << this->instance.size() << "\n";
    for (int i = 0; i < this->instance.size(); ++i) {

        ostream << this->instance.getPoint(i);

        auto finder = this->placements.find(i);
        if(this->placements.end() != finder) {
            Point::Point2D rectCorner = std::get<0>(finder->second);
            ostream << "1 " << std::get<0>(rectCorner) << " " << std::get<1>(rectCorner);
        } else {
            ostream << "0 0 0";
        }
        ostream << std::endl;
    }
    return ostream;
}

