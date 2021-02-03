#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/BasicSolution.hpp>

#include <string>

void readInstance(const std::string& filename, Instance& instance, BasicSolution& solution);

bool parseLine(Instance& instance, const std::string& line, BasicSolution& solution, int counter);

int parsePositiveInteger(const std::string& line);

void checkBoxConsistency(int x, int y, int width, int height, int upperLeftX, int upperLeftY);

Point::Corner parseCornerPlacement(int x, int y, int upperLeftX, int upperLeftY);
