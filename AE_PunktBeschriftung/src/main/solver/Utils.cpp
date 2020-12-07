#include <solver/Utils.hpp>

// calculates a unique ID for each label from pointIdx corner
int getLabelIdx(int pointIdx, Point::Corner corner) {
    return pointIdx * 4 + corner;
}

// calculates the Point-Index back from the labelIdx
int getPointIdxFromLabel(int labelIdx) {
    return labelIdx / 4;
}

// calculates the corner back from the labelIdx
Point::Corner getCornerFromLabel(int labelIdx) {
    return static_cast<Point::Corner>( labelIdx % 4 );
}