//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_POINT2D_HPP
#define UNTITLED_POINT2D_HPP

#include <memory>
#include "Box.hpp"

class Point2D {
private:
    int x;
    int y;
    std::unique_ptr<Box> box;
    friend std::ostream& operator<<(std::ostream&, const Point2D&);

public:
    Point2D(int x, int y, std::unique_ptr<Box> boxParam);
};


#endif //UNTITLED_POINT2D_HPP
