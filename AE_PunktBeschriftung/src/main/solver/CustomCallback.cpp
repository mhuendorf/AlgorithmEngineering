
#include <iostream>
#include <vector>
#include <cmath>

#include <solver/CustomCallback.hpp>
#include <solver/Utils.hpp>

CustomCallback::CustomCallback(Instance& instance, GRBModel& model) : instance{instance}, model{model} {
    heuristic = TrivialSolver();
}

void CustomCallback::callback() {
    //std::cout << "Callback of Type: " << where << std::endl;
    if (where == GRB_CB_MIPNODE) {

        heuristicSolution();

    } else if (where == GRB_CB_MIP) {
        // General MIP callback - stopping if gap is small enough
        double objbst = getDoubleInfo(GRB_CB_MIP_OBJBST); // best objective
        double objbnd = getDoubleInfo(GRB_CB_MIP_OBJBND); // best known bound

        // std::cout << "Best objective value: " << objbst << std::endl
        //          << "Best bound so far: " << objbnd << std::endl;
        
        if (fabs(objbst - objbnd) < 0.05 * (1.0 + fabs(objbst))) {
            std::cout << "Stop early - 5% gap achieved" << std::endl;
            abort();
        }
    }
}

void CustomCallback::cut() {

}



void CustomCallback::heuristicSolution() {
    // 1. get objective value of best known bound?
    // double bestBound = getDoubleInfo(GRB_CB_MIPNODE_OBJBND);

    // 2. calculate heuristic solution based on LP-relaxation
    std::vector<int> suggestions;
    for(int i = 0; i < instance.size()*4; i++) {
        std::string name = "y_" + std::to_string(i);
        int labelValue = getSolution(model.getVarByName(name));
        if(labelValue > 0.5) { // kinda arbitrarily setting this
            suggestions.push_back(i);
        }
    }
    BasicSolution heurSol = heuristic.solve(instance, suggestions);

    std::cout << "Found heuristic solution with size: " << heurSol.size() << std::endl;


    // 3. transform our solution back into a Gurobi-Solution
    for(int i = 0; i < instance.size(); i++) {
        // if a point is in the solution, set x and y-var to 1
        if(heurSol.contains(i)) {
            this->setSolution(model.getVarByName("x_"+std::to_string(i)), 1.0);
            Point::Corner corner = heurSol.getCorner(i);
            this->setSolution(model.getVarByName("y_" + std::to_string(getLabelIdx(i,corner))), 1.0);

            // set all non-selected corners of this point to 0
            for(int other = Point::TOP_LEFT; other != Point::NOT_PLACED; other++) {
                Point::Corner otherCorner = static_cast<Point::Corner>(other);
                if(corner != otherCorner) {
                    this->setSolution(model.getVarByName("y_" + std::to_string(getLabelIdx(i, otherCorner))), 0.0);
                }
            }
        } else {
            // for unselected points, just set everything to false
            this->setSolution(model.getVarByName("x_"+std::to_string(i)), 0.0);
            for(int other = Point::TOP_LEFT; other != Point::NOT_PLACED; other++) {
                Point::Corner otherCorner = static_cast<Point::Corner>(other);
                this->setSolution(model.getVarByName("y_" + std::to_string(getLabelIdx(i, otherCorner))), 0.0);
            }
        }
    }
}