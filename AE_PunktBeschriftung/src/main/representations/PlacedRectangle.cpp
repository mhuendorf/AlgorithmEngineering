//
// Created by Marcel Hündorf on 01.11.20.
//

#include <representations/PlacedRectangle.hpp>


PlacedRectangle::PlacedRectangle(Point2D &topLeft, Point2D &bottomRight,
                                 Defs::Corner placement) : Rectangle(topLeft, bottomRight), placement(placement) {
}

Defs::Corner PlacedRectangle::getPlacement() {
    return this->placement;
}
