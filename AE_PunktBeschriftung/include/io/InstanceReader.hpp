#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/BasicSolution.hpp>

#include <string>

void readInstance(const std::string& filename, Instance& instance, Solution& solution);

void parseLine(Instance& instance, const std::string& line, Solution& solution, int counter);

int parsePositiveInteger(const std::string& line);

void checkBoxConsistency(long x, long y, int width, int height, long upperLeftX, long upperLeftY);

Point::Corner parseCornerPlacement(long x, long y, long upperLeftX, long upperLeftY);
