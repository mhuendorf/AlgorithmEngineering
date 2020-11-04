#ifndef UNTITLED_SOLUTION_HPP
#define UNTITLED_SOLUTION_HPP


#include <iostream>
#include <representations/Instance.hpp>
#include <representations/PlacedRectangle.hpp>
#include <representations/Rectangle.hpp>
#include <tuple>


/**
 * A class that represents a Solution of any Instance.
 */
class Solution {

private:
    
    const Instance& instance;
    //std::shared_ptr<Instance> instance;

    std::vector<PlacedRectangle> labelBoxes;

    std::tuple<int, int> getTopRight(const Point2D &topLeft, int width);

    std::tuple<int, int> getBottomLeft(const Point2D &topLeft, int height);

    std::tuple<int, int> getBottomRight(const Point2D &topLeft, int width, int height);

    friend std::ostream &operator<<(std::ostream &stream, Solution &solution);

public:

    explicit Solution(Instance& instance);

    bool isFeasible();

    void reserve(int num);

    void placeLabel(int pointIdx, Defs::Corner cornerPlacement);

    bool wouldFit(int pointIdx, Defs::Corner placement);
};


#endif //UNTITLED_SOLUTION_HPP
