//
// Created by Marcel Hündorf on 01.11.20.
//

#ifndef UNTITLED_DEFS_HPP
#define UNTITLED_DEFS_HPP

#include <string>

class Defs {
public:
    enum Corner {
        NOT_PLACED = 0, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
    };

    static std::string cornerToString(Corner corner);
};


#endif //UNTITLED_DEFS_HPP
