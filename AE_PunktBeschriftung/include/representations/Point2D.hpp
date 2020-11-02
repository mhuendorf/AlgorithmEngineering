//
// Created by Marcel Hündorf on 27.10.20.
//

#ifndef UNTITLED_POINT2D_HPP
#define UNTITLED_POINT2D_HPP

#include <iostream>

class Point2D {

public:
    Point2D(int x, int y);

    int x;
    int y;
};

std::ostream &operator<<(std::ostream &, const Point2D &);


#endif //UNTITLED_POINT2D_HPP
