//
// Created by Marcel Hündorf on 06.12.20.
//

#ifndef LABEL_MAP_SIMULATEDANNEALINGSOLUTION_HPP
#define LABEL_MAP_SIMULATEDANNEALINGSOLUTION_HPP


#include "BasicSolution.hpp"

class SimulatedAnnealingSolution : public BasicSolution {
private:
    double solutionScore;
    std::vector<std::vector<int>> overlaps;
    double getPointScore(int numOverlaps);

public:
    explicit SimulatedAnnealingSolution(Instance &instance);

    void changePlacement(int pointIdx, int randomNumber);

    void initSolution();

    Point::Corner getCornerPlacement(int pointIdx);

    void printSolution(std::ostream &ostream) override;

    double computeSolutionScore();

    double getSolutionScore();

    void fixSolution();
};


#endif //LABEL_MAP_SIMULATEDANNEALINGSOLUTION_HPP
