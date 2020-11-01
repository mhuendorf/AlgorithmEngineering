//
// Created by Marcel Hündorf on 27.10.20.
//

#include <representations/Solution.hpp>

Solution::Solution(Instance &instance) :  labelBoxes() {
    this->instance = std::make_shared<Instance>(instance);
}

bool Solution::isFeasible() {
    if (labelBoxes.size() < 2) return true;
    for (int i = 0; i < labelBoxes.size()-1; ++i) {
        cout << i << " ";
        for (int j = i+1; j < labelBoxes.size() ; ++j) {
            if (labelBoxes.at(i).isOverlapping(labelBoxes.at(j))) {
                return false;
            }
        }
        cout << endl;
    }
    return true;
}

void Solution::placeLabel(int pointIdx, Defs::Corner cornerPlacement) {
    std::shared_ptr<PointWithLabel> pwl = instance->getPoint(pointIdx);
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            Point2D topLeft(pwl->getX(), pwl->getY());
            Point2D bottomRight(pwl->getX() + pwl->getBoxWidth(), pwl->getY() + pwl->getBoxHeight());
            labelBoxes.emplace_back(topLeft, bottomRight, cornerPlacement);
            break;
        }
        case Defs::TOP_RIGHT: {
            Point2D topLeft(pwl->getX() - pwl->getBoxWidth(), pwl->getY());
            Point2D bottomRight(pwl->getX(), pwl->getY() + pwl->getBoxHeight());
            labelBoxes.emplace_back(topLeft, bottomRight, cornerPlacement);
            break;
        }
        case Defs::BOTTOM_LEFT:{
            Point2D topLeft(pwl->getX(), pwl->getY() + pwl->getBoxHeight());
            Point2D bottomRight(pwl->getX() + pwl->getBoxWidth(), pwl->getY());
            labelBoxes.emplace_back(topLeft, bottomRight, cornerPlacement);
            break;
        }
        case Defs::BOTTOM_RIGHT:{
            Point2D topLeft(pwl->getX() - pwl->getBoxWidth(), pwl->getY() + pwl->getBoxHeight());
            Point2D bottomRight(pwl->getX(), pwl->getY());
            labelBoxes.emplace_back(topLeft, bottomRight, cornerPlacement);
            break;
        }
        default:
            throw 1;
    }
}

