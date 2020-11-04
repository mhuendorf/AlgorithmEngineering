#include <representations/Solution.hpp>

Solution::Solution(Instance &instance) : labelBoxes() {
    this->instance = std::make_shared<Instance>(instance);
}

bool Solution::isFeasible() {
    if (labelBoxes.size() < 2) return true;
    for (int i = 0; i < labelBoxes.size() - 1; ++i) {
        for (int j = i + 1; j < labelBoxes.size(); ++j) {
            if (labelBoxes.at(i).isOverlapping(labelBoxes.at(j))) {
                return false;
            }
        }
    }
    return true;
}

void Solution::placeLabel(int pointIdx, Defs::Corner cornerPlacement) {
    std::shared_ptr<PointWithLabel> pwl = instance->getPoint(pointIdx);
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            int x1 = pwl->getX();
            int y1 = pwl->getY();
            int x2 = pwl->getX() + pwl->getBoxWidth();
            int y2 = pwl->getY() - pwl->getBoxHeight();
            labelBoxes.emplace_back(x1, y1, x2, y2, cornerPlacement, pointIdx);
            break;
        }
        case Defs::TOP_RIGHT: {
            int x1 = pwl->getX() - pwl->getBoxWidth();
            int y1 = pwl->getY();
            int x2 = pwl->getX();
            int y2 = pwl->getY() - pwl->getBoxHeight();
            labelBoxes.emplace_back(x1, y1, x2, y2, cornerPlacement, pointIdx);
            break;
        }
        case Defs::BOTTOM_LEFT: {
            int x1 = pwl->getX();
            int y1 = pwl->getY() + pwl->getBoxHeight();
            int x2 = pwl->getX() + pwl->getBoxWidth();
            int y2 = pwl->getY();
            labelBoxes.emplace_back(x1, y1, x2, y2, cornerPlacement, pointIdx);
            break;
        }
        case Defs::BOTTOM_RIGHT: {
            int x1 = pwl->getX() - pwl->getBoxWidth();
            int y1 = pwl->getY() + pwl->getBoxHeight();
            int x2 = pwl->getX();
            int y2 = pwl->getY();
            labelBoxes.emplace_back(x1, y1, x2, y2, cornerPlacement, pointIdx);
            break;
        }
        default:
            throw 1;
    }
}

std::tuple<int, int> Solution::getTopRight(const Point2D &topLeft, int width) {
    return std::tuple<int, int>(topLeft.x + width, topLeft.y);
}

std::tuple<int, int> Solution::getBottomLeft(const Point2D &topLeft, int height) {
    return std::tuple<int, int>(topLeft.x, topLeft.y - height);
}

std::tuple<int, int> Solution::getBottomRight(const Point2D &topLeft, int width, int height) {
    return std::tuple<int, int>(topLeft.x + width, topLeft.y - height);
}

bool Solution::wouldFit(int pointIdx, Defs::Corner placement) {
    PlacedRectangle pr(*instance->getPoint(pointIdx), placement, pointIdx);
    for (auto rect : labelBoxes) {
        if (rect.isOverlapping(pr)) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(ostream &stream, Solution &solution) {
    stream << solution.instance->size() << endl;
    for (int i = 0; i < solution.instance->size(); ++i) {
        bool isSet = false;
        for (int j = 0; j < solution.labelBoxes.size(); ++j) {
            if (solution.labelBoxes.at(j).getPointIdx() == i) {
                stream << *solution.instance->getPoint(i) << "  \t1\t" << solution.labelBoxes.at(j).getTopLeft().x
                       << "\t"
                       << solution.labelBoxes.at(j).getTopLeft().y << std::endl;
                isSet = true;
                break;
            }
        }
        if (!isSet)
            stream << *solution.instance->getPoint(i) << "  \t0\t0\t0" << std::endl;
    }
    return stream;
}

