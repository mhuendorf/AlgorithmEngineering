#pragma once 

#include <representations/Point.hpp>

// calculates a unique ID for each label from pointIdx corner
int getLabelIdx(int pointIdx, Point::Corner corner);

// calculates the Point-Index back from the labelIdx
int getPointIdxFromLabel(int labelIdx);

// calculates the corner back from the labelIdx
Point::Corner getCornerFromLabel(int labelIdx);