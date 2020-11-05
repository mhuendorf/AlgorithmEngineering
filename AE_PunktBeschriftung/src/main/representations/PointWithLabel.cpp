#include <representations/PointWithLabel.hpp>
#include <representations/Box.hpp>
#include <iomanip>


PointWithLabel::PointWithLabel(int x, int y, std::shared_ptr<Box> boxParam) : x(x), y(y), box(std::move(boxParam)) {

}

std::ostream &operator<<(std::ostream &ostream, const PointWithLabel &point2D) {
    return ostream << point2D.x << "\t" << point2D.y << "\t" << *point2D.box;
}

int PointWithLabel::getBoxHeight() const {
    return box.get()->getHeight();
}

int PointWithLabel::getBoxWidth() const {
    return box.get()->getWidth();
}

int PointWithLabel::getX() const {
    return x;
}

int PointWithLabel::getY() const {
    return y;
}