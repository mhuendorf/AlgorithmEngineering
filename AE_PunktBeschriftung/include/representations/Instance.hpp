//
// Created by Marcel Hündorf on 26.10.20.
//

#ifndef UNTITLED_INSTANCE_HPP
#define UNTITLED_INSTANCE_HPP

#include <stack>
#include <vector>
#include <representations/PointWithLabel.hpp>

class Instance {
private:
    std::vector< std::shared_ptr<PointWithLabel> > points;
    friend std::ostream& operator<<(std::ostream& ostream, const Instance& instance);

public:
    Instance();

    void operator+(std::shared_ptr<PointWithLabel> point2D);
    int size();
    std::shared_ptr<PointWithLabel> getPoint(int idx);
};


#endif //UNTITLED_INSTANCE_HPP
