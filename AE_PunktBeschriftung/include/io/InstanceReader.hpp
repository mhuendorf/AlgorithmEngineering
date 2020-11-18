#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/SolutionWithGraph.hpp>

#include <string>

void readInstance(const std::string& filename, Instance& instance, SolutionWithGraph& solution);

void parseLine(Instance& instance, const std::string& line, SolutionWithGraph& solution, int counter);

int parsePositiveInteger(const std::string& line);

void checkBoxConsistency(int x, int y, int width, int height, int upperLeftX, int upperLeftY);

Point::Corner parseCornerPlacement(int x, int y, int upperLeftX, int upperLeftY);
