#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>

#include <string>

Instance readInstance(const std::string& filename);

void parseLine(Instance& instance, const std::string& line);

int parsePositiveInteger(const std::string& line);

void checkBoxConsistency(int x, int y, int width, int height, int upperLeftX, int upperLeftY);

Point::Corner parseCornerPlacement(int x, int y, int upperLeftX, int upperLeftY);
