//
// Created by Marcel Hündorf on 01.11.20.
//

#include <representations/PlacedRectangle.hpp>


PlacedRectangle::PlacedRectangle(int x1, int y1, int x2, int y2, Defs::Corner placement, int pointIdx)
        : Rectangle(x1, y1, x2, y2),
          placement(placement),
          pointIdx(pointIdx) {
}

PlacedRectangle::PlacedRectangle(PointWithLabel &pointWithLabel, Defs::Corner placement, int pointIdx)
        : Rectangle(getX1(pointWithLabel, placement), getY1(pointWithLabel, placement),
                    getX2(pointWithLabel, placement), getY2(pointWithLabel, placement)),
          placement(placement),
          pointIdx(pointIdx) {
}

Defs::Corner PlacedRectangle::getPlacement() {
    return this->placement;
}

std::ostream &operator<<(ostream &stream, PlacedRectangle &placedRectangle) {
    stream << static_cast<Rectangle &>(placedRectangle) << Defs::cornerToString(placedRectangle.getPlacement());
    return stream;
}

bool PlacedRectangle::isOverlapping(const PlacedRectangle &placedRectangle) const {
    return Rectangle::isOverlapping(placedRectangle);
}

int PlacedRectangle::getX1(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement) {
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            return pointWithLabel.getX();
        }
        case Defs::TOP_RIGHT: {
            return pointWithLabel.getX() - pointWithLabel.getBoxWidth();
        }
        case Defs::BOTTOM_LEFT: {
            return pointWithLabel.getX();
        }
        case Defs::BOTTOM_RIGHT: {
            return pointWithLabel.getX() - pointWithLabel.getBoxWidth();
        }
        default:
            throw 1;
    }
}

int PlacedRectangle::getY1(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement) {
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            return pointWithLabel.getY();
        }
        case Defs::TOP_RIGHT: {
            return pointWithLabel.getY();
        }
        case Defs::BOTTOM_LEFT: {
            return pointWithLabel.getY() + pointWithLabel.getBoxHeight();
        }
        case Defs::BOTTOM_RIGHT: {
            return pointWithLabel.getY() + pointWithLabel.getBoxHeight();
        }
        default:
            throw 1;
    }
}

int PlacedRectangle::getX2(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement) {
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            return pointWithLabel.getX() + pointWithLabel.getBoxWidth();
        }
        case Defs::TOP_RIGHT: {
            return pointWithLabel.getX();
        }
        case Defs::BOTTOM_LEFT: {
            return pointWithLabel.getX() + pointWithLabel.getBoxWidth();
        }
        case Defs::BOTTOM_RIGHT: {
            return pointWithLabel.getX();
        }
        default:
            throw 1;
    }
}

int PlacedRectangle::getY2(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement) {
    switch (cornerPlacement) {
        case Defs::TOP_LEFT: {
            return pointWithLabel.getY() - pointWithLabel.getBoxHeight();
        }
        case Defs::TOP_RIGHT: {
            return pointWithLabel.getY() - pointWithLabel.getBoxHeight();
        }
        case Defs::BOTTOM_LEFT: {
            return pointWithLabel.getY();
        }
        case Defs::BOTTOM_RIGHT: {
            return pointWithLabel.getY();
        }
        default:
            throw 1;
    }
}

int PlacedRectangle::getPointIdx() {
    return pointIdx;
}

