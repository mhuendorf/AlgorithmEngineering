//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_BOX_HPP
#define UNTITLED_BOX_HPP


#include <string>

class Box {
private:
    int width;
    int height;
    std::string label;
    friend std::ostream& operator<<(std::ostream&, const Box&);

public:
    Box(int width, int height, std::string label);
};


#endif //UNTITLED_BOX_HPP
