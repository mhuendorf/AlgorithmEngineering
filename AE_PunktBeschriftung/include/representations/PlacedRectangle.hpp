#ifndef UNTITLED_PLACEDRECTANGLE_HPP
#define UNTITLED_PLACEDRECTANGLE_HPP

#include <representations/Rectangle.hpp>
#include <representations/Defs.hpp>
#include <representations/PointWithLabel.hpp>

class PlacedRectangle : public Rectangle {
private:
    Defs::Corner placement;
    int pointIdx;

    static int getX1(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement);

    static int getY1(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement);

    static int getX2(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement);

    static int getY2(PointWithLabel &pointWithLabel, Defs::Corner cornerPlacement);

    friend std::ostream &operator<<(std::ostream &stream, PlacedRectangle &placedRectangle);

public:
    PlacedRectangle(int x1, int y1, int x2, int y2, Defs::Corner placement, int pointIdx);

    PlacedRectangle(PointWithLabel &pointWithLabel, Defs::Corner placement, int pointIdx);

    bool isOverlapping(const PlacedRectangle &placedRectangle) const;

    int getPointIdx();

    Defs::Corner getPlacement();
};


#endif //UNTITLED_PLACEDRECTANGLE_HPP
