#ifndef LABEL_MAP_SOLUTION_HPP
#define LABEL_MAP_SOLUTION_HPP


#include "Instance.hpp"

class Solution {
protected:
    const Instance instance;

public:
    virtual std::ostream &operator<<(std::ostream &ostream) = 0;

    explicit Solution(Instance &instance1);

    [[nodiscard]] virtual bool isFeasible() const = 0;

    virtual void setLabel(int idx, Point::Corner corner) = 0;

    [[nodiscard]] const Point& getPoint(int idx) const;

    [[nodiscard]] virtual int size() const = 0;

};



#endif //LABEL_MAP_SOLUTION_HPP
