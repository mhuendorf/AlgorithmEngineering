//
// Created by Marcel Hündorf on 16.11.20.
//

#ifndef LABEL_MAP_SOLUTION_H
#define LABEL_MAP_SOLUTION_H


#include "Instance.hpp"

class Solution {
protected:
    Instance instance;

public:
    virtual std::ostream &operator<<(std::ostream &ostream) = 0;

    explicit Solution(Instance &instance1);

    [[nodiscard]] virtual bool isFeasible() = 0;

    virtual void setLabel(int idx, Point::Corner corner) = 0;

    [[nodiscard]] const Point& getPoint(int idx) const;

    virtual std::vector<int> &getLabelledPoints() = 0;

    [[nodiscard]] virtual int size() const = 0;

};


#endif //LABEL_MAP_SOLUTION_H
