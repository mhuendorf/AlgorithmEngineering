#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/Solution.hpp>

#include <map>

class BasicSolution : public Solution {

private:

    std::map<int, Point::Rectangle> placements; // maps point-indices to rectangles
    std::map<int, Point::Corner> corners; // maps point-indices to the corner-info

    friend std::ostream& operator<<(std::ostream &ostream, const BasicSolution &solution);

public:

    BasicSolution(const Instance& instance);

    BasicSolution& operator=(const BasicSolution& other);

    void setLabel(int idx, Point::Corner corner);

    void resetLabel(int idx);

    bool contains(int idx) const;

    bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    int size() const;

    bool isFeasible() const;

    Point::Corner const getCorner(int pointIdx) const;

    void printSolution(std::ostream &ostream);

};