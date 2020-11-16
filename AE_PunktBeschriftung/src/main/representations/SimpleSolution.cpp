//
// Created by Marcel Hündorf on 16.11.20.
//

#include <iostream>
#include "representations/SimpleSolution.hpp"

SimpleSolution::SimpleSolution(Instance &instance) : Solution(instance), labelled_points{} {
}

bool SimpleSolution::isFeasible() {
    for (std::size_t i = 0; i < labelled_points.size(); i++) {
        Point p = this->getPoint(labelled_points[i]);
        for (std::size_t j = i + 1; j < labelled_points.size(); j++) {
            Point other = this->getPoint(labelled_points[j]);

            if (p.checkCollision(other)) {
                throw std::runtime_error("Points " + p.getName() + " and " + other.getName() + " overlap!");
            }
        }
    }
    return true;
}


// sets the label for point at idx at the given Corner
void SimpleSolution::setLabel(int idx, Point::Corner corner) {

    // mark this point as labelled
    this->labelled_points.push_back(idx);
    this->getPoint(idx).setPlacement(corner);
}

// returns the number of points
int SimpleSolution::size() const {
    return this->labelled_points.size();
}

std::vector<int> &SimpleSolution::getLabelledPoints() {
    return this->labelled_points;
}

std::ostream &SimpleSolution::operator<<(std::ostream &ostream) {
    ostream << instance.size() << "\n";
    for (int i = 0; i < instance.size(); ++i) {
        Point p = getPoint(i);
        if (p.getPlacement() == Point::NOT_PLACED)
            ostream << p << "\t0 0 0" << std::endl;
        else {
            auto coords = p.getCoordsForPlacement(p.getPlacement());
            auto top_left = std::get<0>(coords);
            ostream << p << "\t1 " << std::get<0>(top_left) << " " << std::get<1>(top_left) << std::endl;
        }
    }
    return ostream;
}


