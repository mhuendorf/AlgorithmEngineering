#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>

#include <map>

class Solution {

private:

    const Instance& instance;

    std::map<int, Point::Rectangle> placements; // maps point-indices to rectangles
    std::map<int, Point::Corner> corners; // maps point-indices to the corner-info

    friend std::ostream& operator<<(std::ostream &ostream, const Solution &solution);

public:

    Solution(const Instance& instance);

    Solution& operator=(const Solution& other);

    void setLabel(int idx, Point::Corner corner);

    void resetLabel(int idx);

    bool contains(int idx) const;

    bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    int size() const;

    bool isFeasible() const;

    Point::Corner const getCorner(int pointIdx) const;



};