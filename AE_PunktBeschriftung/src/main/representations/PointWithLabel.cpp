#include <representations/PointWithLabel.hpp>
#include <representations/Box.hpp>
#include <iomanip>


PointWithLabel::PointWithLabel(int x, int y, std::shared_ptr<Box> boxParam) : x(x), y(y), box(std::move(boxParam)) {

}

std::ostream &operator<<(std::ostream &ostream, const PointWithLabel &point2D) {
    return ostream << std::setw(6) << point2D.x << std::setw(6) << point2D.y << *point2D.box;
}

int PointWithLabel::getBoxHeight() {
    return box.get()->getHeight();
}

int PointWithLabel::getBoxWidth() {
    return box.get()->getWidth();
}

int PointWithLabel::getX() {
    return x;
}

int PointWithLabel::getY() {
    return y;
}