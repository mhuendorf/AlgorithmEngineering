#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/Solver.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <set>

struct Subproblem {
    std::set<int> Ri;
    std::map<int, bool> border;
};

class PopmusicSolver : public Solver {

private:

    Instance& instance;
    BasicSolution solution;

    // config parameters for TabuSearch
    int maxTabuIt;
    int tenure;
    // int minCandidateLSize;
    // int minTabuSize;
    // double candidateBaseFactor;
    // double reductionFactor;
    // double tabuFactor;
    // double growingFactor;
    
    // overlap information of labels, obtained from FALPSolver
    std::vector< std::vector<int> > overlaps;

    // r: ideal size of the subproblem 
    // si: seed part
    // border: control array
    Subproblem createSubProblem(const Instance& instance, size_t r, int si) const;
    
    void tabuSearch(const Subproblem& sub);

public:

    PopmusicSolver(Instance& instance) 
        : instance(instance), solution(BasicSolution(instance)), maxTabuIt(5), tenure(5) {};

    BasicSolution solve(Instance& instance) override;

};
