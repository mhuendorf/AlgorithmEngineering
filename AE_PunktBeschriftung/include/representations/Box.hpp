#ifndef UNTITLED_BOX_HPP
#define UNTITLED_BOX_HPP

#include <string>

class Box {
private:
    int width;
    int height;
    std::string label;

    friend std::ostream &operator<<(std::ostream &, const Box &);

public:
    Box(int width, int height, std::string label);

    int getHeight();

    int getWidth();
};


#endif //UNTITLED_BOX_HPP
