//
// Created by Marcel Hündorf on 27.10.20.
//

#ifndef UNTITLED_SOLUTION_HPP
#define UNTITLED_SOLUTION_HPP


#include <iostream>
#include "Instance.hpp"

enum corner{notPLaced = 0, topRight, topLeft, bottomRight, bottomLeft};

class Solution {
private:
    std::unique_ptr<Instance> instance;
    std::vector<corner> boxPlacements;

public:
    Solution(Instance &instance);
    bool isFeasible();
};


#endif //UNTITLED_SOLUTION_HPP
