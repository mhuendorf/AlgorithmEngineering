#pragma once

#include <representations/Instance.hpp>
#include <representations/Point.hpp>
#include <representations/Solution.hpp>

#include <map>

 class BasicSolution : public Solution {

protected:
    std::map<int, Point::Rectangle> placements;

private:

     std::map<int, Point::Corner> corners; // maps point-indices to the corner-info
     friend std::ostream& operator<<(std::ostream &ostream, const BasicSolution &solution);

public:
    BasicSolution(const BasicSolution &basicSolution);

    explicit BasicSolution(const Instance& instance);

    BasicSolution& operator=(const BasicSolution& other);

    void setLabel(int idx, Point::Corner corner) override;

    void resetLabel(int idx);

    bool contains(int idx) const;

    bool checkCollision(const Point& p, Point::Corner placement, int otherIdx) const;

    int size() const override;

    bool isFeasible() const override;

    Point::Corner getCorner(int pointIdx) const;

    void printSolution(std::ostream &ostream) override;

};