#pragma once

#include <representations/Instance.hpp>
#include <representations/Solution.hpp>

#include <queue>
#include <list>
#include <functional>

// struct to store labels in priority Q
struct QElem {

    QElem(int idx, Point::Corner corner, int laps) : idx(idx), corner(corner), overlaps(laps) {};

    int idx;
    Point::Corner corner;
    int overlaps;
};

// The solver used to generate initial Solutions in POPMUSIC
class FALPSolver {

private:

    // comparison function to compare QElems by number of overlaps
    std::function<bool(QElem, QElem)> labelCmp = [](QElem left, QElem right) { return left.overlaps > right.overlaps; };
    // priorityQ that stores QElems
    std::priority_queue<QElem, std::vector<QElem>, decltype(labelCmp)> labelQ;

    std::list< std::list<int> > overlaps;

    // method for putting all Labels into a priority Q
    void setupLabelQ(const Instance& instance);

public:

    FALPSolver();

    Solution solve(Instance& instance);
    
};


