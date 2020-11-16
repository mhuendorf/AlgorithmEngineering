//
// Created by Marcel Hündorf on 16.11.20.
//

#ifndef LABEL_MAP_SIMPLESOLUTION_HPP
#define LABEL_MAP_SIMPLESOLUTION_HPP


#include "Solution.hpp"

class SimpleSolution : public Solution {
private:
    std::vector<int> labelled_points; // contains all indices of points with actual labels
public:
    explicit SimpleSolution(Instance &instance);

    std::ostream &operator<<(std::ostream &ostream) override;

    [[nodiscard]] bool isFeasible() override;

    void setLabel(int idx, Point::Corner corner) override;

    std::vector<int> &getLabelledPoints() override;

    [[nodiscard]]  int size() const override;
};


#endif //LABEL_MAP_SIMPLESOLUTION_HPP
