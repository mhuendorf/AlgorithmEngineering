#include <representations/Solution.hpp>
#include <representations/Point.hpp>

#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;


Solution::Solution(const Instance& instance) : instance{instance}, placements{} {}


int Solution::size() const {
    return placements.size();
}


std::ostream& operator<<(std::ostream &ostream, const Solution &solution) {
    
    ostream << solution.instance.size() << "\n";
    for (int i = 0; i < solution.instance.size(); ++i) {

        ostream << solution.instance.getPoint(i);

        std::map<int, Rectangle>::const_iterator finder = solution.placements.find(i);
        if(solution.placements.end() != finder) {
            Point2D rectCorner = std::get<0>(finder->second);
            ostream << "1 " << std::get<0>(rectCorner) << " " << std::get<1>(rectCorner);
        } else {
            ostream << "0 0 0";
        }
        ostream << std::endl;
    }
    return ostream;
}

bool Solution::isFeasible() const {

    std::map<int, Rectangle>::const_iterator it = placements.cbegin();
    while(it != placements.end()) {
        int idx = it->first;
        Rectangle rect = it->second;

        const Point& p = instance.getPoint(idx);
        for(const Point& other : p.getNeighbours()) {
            std::map<int, Rectangle>::const_iterator finder = placements.find(other.getIdx());
            if(placements.end() != finder) {
                if(Point::checkCollision(rect, finder->second)) {
                    throw std::runtime_error("Points " + p.getName() + " and " + other.getName() + " overlap!");
                }
            }
            
        }

        it++;
    }

    // checked everything, never ran into a collision
    return true;
}

void Solution::setLabel(int idx, Point::Corner corner) {

    Rectangle rect = instance.getPoint(idx).getCoordsForPlacement(corner);
    placements.insert(std::make_pair(idx, rect));

}

bool Solution::contains(int idx) const {
    std::map<int, Rectangle>::const_iterator finder = placements.find(idx);
    return placements.end() != finder;
}

bool Solution::checkCollision(const Point& p, Point::Corner placement, int otherIdx) const {

    if(!contains(otherIdx)) {
        return false; // can't collide if the other one isn't even set
    }

    Rectangle rect1 = p.getCoordsForPlacement(placement);
    Rectangle rect2 = placements.find(otherIdx)->second;

    return Point::checkCollision(rect1, rect2);
}