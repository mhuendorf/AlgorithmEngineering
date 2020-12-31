#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/Solver.hpp>

#include <queue>
#include <vector>
#include <set>
#include <functional>
#include <iostream>

// struct to store labels in priority Q
struct QElem {

    QElem(int idx, Point::Corner corner, int laps) : idx(idx), corner(corner), overlaps(laps) {};

    int idx; // the index of the point
    Point::Corner corner; // the corner of the label
    int overlaps; // number of overlaps of this label

    bool operator==(QElem& other) const { return other.idx == idx && other.corner == corner; };
};

// The solver used to generate initial Solutions in POPMUSIC
class FALPSolver : public Solver {

private:

    // comparison function to compare QElems by number of overlaps
    std::function<bool(QElem, QElem)> labelCmp = [](QElem left, QElem right) { return left.overlaps < right.overlaps; };
    // priorityQ that stores QElems
    std::multiset<QElem, decltype(labelCmp) > labelQ;

    std::vector< std::vector<int> > overlaps;

    // method for putting all Labels into a priority Q
    void setupLabelQ(const Instance& instance);

    void setBestLabels(Solution& solution);

    // DEBUG
    void printSet();

public:

    FALPSolver();

    BasicSolution solve(Instance& instance) override;

    std::vector< std::vector<int> >& getOverlaps();

};
