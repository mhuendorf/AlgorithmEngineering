#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>

#include <map>

class Solution {

private:

    const Instance& instance;

    std::map<int, Rectangle> placements;

    friend std::ostream& operator<<(std::ostream &ostream, const Solution &solution);

public:

    Solution(const Instance& instance);

    void setLabel(int idx, Point::Corner corner);

    bool contains(int idx) const;

    bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    int size() const;

    bool isFeasible() const;

};