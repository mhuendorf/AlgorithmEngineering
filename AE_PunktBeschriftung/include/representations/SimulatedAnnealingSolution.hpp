#pragma once

#include <representations/BasicSolution.hpp>

class SimulatedAnnealingSolution : public BasicSolution {

private:

    double solutionScore;
    std::vector<std::vector<int>> overlaps;
    static double getPointScore(int numOverlaps);

public:

    explicit SimulatedAnnealingSolution(Instance &instance);

    void changePlacement(int pointIdx, int randomNumber);

    void initSolution();

    Point::Corner getCornerPlacement(int pointIdx);

    void printSolution(std::ostream &ostream) override;

    double computeSolutionScore();

    [[nodiscard]] double getSolutionScore() const;

    void fixSolution();
};