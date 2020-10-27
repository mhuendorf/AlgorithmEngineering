//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_POINT2D_HPP
#define UNTITLED_POINT2D_HPP


#include "Box.hpp"

class Point2D {
private:
    Box* box;
    int x;
    int y;
    friend std::ostream& operator<<(std::ostream&, const Point2D&);

public:
    Point2D(int x, int y, Box *box);
};


#endif //UNTITLED_POINT2D_HPP
