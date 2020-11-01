//
// Created by Marcel Hündorf on 01.11.20.
//

#ifndef UNTITLED_PLACEDRECTANGLE_HPP
#define UNTITLED_PLACEDRECTANGLE_HPP

#include <representations/Rectangle.hpp>
#include <representations/Defs.hpp>

class PlacedRectangle : public Rectangle {
private:
    Defs::Corner placement;

public:
    PlacedRectangle(Point2D &topLeft, Point2D &bottomRight, Defs::Corner placement);
    Defs::Corner getPlacement();
};


#endif //UNTITLED_PLACEDRECTANGLE_HPP
