#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/Solution.hpp>

#include <map>

class SolutionWithGraph : Solution {

private:

    std::map<int, Point::Rectangle> placements;

    friend std::ostream& operator<<(std::ostream &ostream, const SolutionWithGraph &solution);

public:

    explicit SolutionWithGraph(Instance &instance);

    void setLabel(int idx, Point::Corner corner) override;

    bool contains(int idx) const;

    bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    int size() const override;

    bool isFeasible() const override;

    std::ostream &operator<<(std::ostream &ostream) override;

};