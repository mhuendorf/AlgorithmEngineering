
#include <iostream>
#include <vector>
#include <cmath>

#include <solver/CustomCallback.hpp>
#include <solver/Utils.hpp>

CustomCallback::CustomCallback(Instance& instance, GRBModel& model) : instance{instance}, model{model} {
    heuristic = TrivialSolver();
    heuristicInsertions = 0;
}

void CustomCallback::callback() {

    if (where == GRB_CB_MIPNODE && GRB_CB_MIPNODE_STATUS == GRB_OPTIMAL) {

        heuristicSolution();
        
    } else if(where == GRB_CB_MIPSOL) { // found a new solution

        // cut();

    } else if (where == GRB_CB_MIP) {

        // // General MIP callback - stopping if gap is small enough
        // double objbst = getDoubleInfo(GRB_CB_MIP_OBJBST); // best objective
        // double objbnd = getDoubleInfo(GRB_CB_MIP_OBJBND); // best known bound

        // // // std::cout << "Best objective value: " << objbst << std::endl
        // // //          << "Best bound so far: " << objbnd << std::endl;
        
        // if (fabs(objbst - objbnd) < 0.03 * (1.0 + fabs(objbst))) {
        //     //std::cout << "Stop early - 5% gap achieved" << std::endl;
        //     abort();
        // }
    }
}

void CustomCallback::cut() {
    // walk over all labels
    // TODO get rid of this: instead, write a method that tells you directly what was wrong
    for(int i = 0; i < instance.size()*4; i++) {

        // get the first variable
        std::string name = "y_"+std::to_string(i);
        GRBVar var1 = model.getVarByName(name);
        double value = getSolution(var1);

        // if the label is set
        if(value == 1) {
            
            // find its point and the rectangle for the placement it has
            Point p = instance.getPoint(getPointIdxFromLabel(i));
            Point::Rectangle rect = p.getCoordsForPlacement(getCornerFromLabel(i));
            bool addedConstraints = false;

            // walk over all neighbours and ...
            for(auto it = p.getNeighbours().begin(); it != p.getNeighbours().end(); it++) {
                Point otherPoint = (*(*it));
                int otherIdx = otherPoint.getIdx();

                // ... all their label positions
                for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                    Point::Rectangle otherRect = otherPoint.getCoordsForPlacement(static_cast<Point::Corner>(corner));

                    // check if collision is even possible
                    if(Point::checkCollision(rect, otherRect)) {
                        int labelIdx = getLabelIdx(otherIdx, static_cast<Point::Corner>(corner));
                        GRBVar var2 = model.getVarByName("y_"+std::to_string(labelIdx));
                        double otherValue = getSolution(var2);

                        // so they collide and both actually are somewhat set: add constraint to prevent overlap

                        if(otherValue == 1) {
                            // std::cout << "ADDING constraint lazy" << std::endl;
                            this->addLazy(var1 + var2 <= 1);
                            addedConstraints = true;
                            return; // was intended for testing but works
                        }
                    }
                }
            }
            if(addedConstraints) {
                return;
            }
        }
    }
}

void CustomCallback::heuristicSolution() {

    try {

        // calculate heuristic solution based on LP-relaxation
        std::vector<int> suggestions;
        for(int i = 0; i < instance.size()*4; i++) {
            std::string name = "y_" + std::to_string(i);
            double labelValue = getNodeRel(model.getVarByName(name));
            if(labelValue > 0.5) { // 0.5 works really well, actually
                suggestions.push_back(i);
            }
        }
        BasicSolution heurSol = heuristic.solve(instance, suggestions);

        // std::cout << heurSol.isFeasible() << std::endl;

        // transform our solution back into a Gurobi-Solution
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

        //std::cout << "Survived Heuristic without issues" << std::endl;

    } catch(GRBException e) {
        std::cout << "Exception in heuristic" << std::endl;
        std::cout << e.getMessage() << ", Error Code: "<< e.getErrorCode() << std::endl;
    }
}