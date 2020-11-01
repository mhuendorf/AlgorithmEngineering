//
// Created by Marcel Hündorf on 27.10.20.
//

#ifndef UNTITLED_SOLUTION_HPP
#define UNTITLED_SOLUTION_HPP


#include <iostream>
#include <representations/Instance.hpp>
#include <representations/PlacedRectangle.hpp>
#include <representations/Rectangle.hpp>


class Solution {
private:
    std::shared_ptr<Instance> instance;
    std::vector<PlacedRectangle> labelBoxes;

public:
    explicit Solution(Instance &instance);
    bool isFeasible();
    void placeLabel(int pointIdx, Defs::Corner cornerPlacement);
};


#endif //UNTITLED_SOLUTION_HPP
