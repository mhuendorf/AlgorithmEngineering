#ifndef INSTANCE_READER_HPP
#define INSTANCE_READER_HPP

#include <string>

#include <representations/Instance.hpp>
#include <representations/Solution.hpp>

void readInstance(Instance& instance, const std::string& filename);

void readInstanceAndSolution(Instance& instance, Solution& solution, const std::string& filename);

std::shared_ptr<PointWithLabel> parseLine(std::string const& line);

int parsePositiveInteger(const std::string& line);

void checkBoxConsistency(int x, int y, int width, int height, int upperLeftX, int upperLeftY);
#endif //INSTANCE_READER_HPP
