#include <representations/Point2D.hpp>

Point2D::Point2D(int x, int y) : x(x), y(y) {
}

std::ostream &operator<<(std::ostream &ostream, const Point2D &point2D) {
    ostream << "(" << point2D.x << ", " << point2D.y << ")";
    return ostream;
}
