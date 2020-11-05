#ifndef UNTITLED_POINTWITHLABEL_HPP
#define UNTITLED_POINTWITHLABEL_HPP

#include <memory>
#include <representations/Box.hpp>

class PointWithLabel {
private:
    int x;
    int y;
    std::shared_ptr<Box> box;

    friend std::ostream &operator<<(std::ostream &, const PointWithLabel &);

public:
    PointWithLabel(int x, int y, std::shared_ptr<Box> boxParam);

    int getX() const;

    int getY() const;

    int getBoxHeight() const;

    int getBoxWidth() const;
};


#endif //UNTITLED_POINTWITHLABEL_HPP
