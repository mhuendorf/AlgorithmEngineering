#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/Solution.hpp>

#include <map>

 class BasicSolution : public Solution {

 protected:
    std::map<int, Point::Rectangle> placements;

public:
    BasicSolution(const BasicSolution &basicSolution);

    explicit BasicSolution(Instance &instance);

    void setLabel(int idx, Point::Corner corner) override;

    [[nodiscard]] bool contains(int idx) const;

    [[nodiscard]] bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    [[nodiscard]] int size() const override;

    [[nodiscard]] bool isFeasible() const override;

    void printSolution(std::ostream &ostream) override;

};