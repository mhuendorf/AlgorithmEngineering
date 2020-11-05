#include <representations/Defs.hpp>


std::string Defs::cornerToString(Defs::Corner corner) {
    switch (corner) {
        case TOP_LEFT:
            return "placed at the top left corner";
        case TOP_RIGHT:
            return "placed at the top right corner";
        case BOTTOM_LEFT:
            return "placed at the bottom left corner";
        case BOTTOM_RIGHT:
            return "placed at the bottom right corner";
        default:
            return "not placed anywhere";
    }
}