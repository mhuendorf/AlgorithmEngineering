#include <solver/ExactSolver.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/Utils.hpp>
#include <solver/CustomCallback.hpp>

#include <iostream>
#include <vector>

#include "gurobi_c++.h"

BasicSolution ExactSolver::solve(Instance& instance) {

    BasicSolution solution(instance);

    try {

        // Create an environment
        GRBEnv env = GRBEnv(true);
        env.set("LogFile", "exactSolver.log");
        env.start();

        // Create an empty model
        GRBModel model = GRBModel(env);

        // objective value
        GRBLinExpr obj = 0.0;

        // stores variables x_i for features 0 to n-1
        std::vector<GRBVar> xVars;
        xVars.reserve(instance.size());

        // stores variables y_i for labels 0 to 4n-1
        std::vector<GRBVar> yVars;
        yVars.reserve(instance.size()*4);

        // stores label-indices that will be needed for constraints
        std::vector<std::tuple<int, int> > conflicts;

        for(const Point::Ptr& p : instance.getPoints()) {

            // create a variable x that represents whether this feature was set or not
            int pointIdx = p->getIdx();
            GRBVar x = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x_" + std::to_string(pointIdx));
            obj += x;
            xVars.push_back(x);

            std::array<GRBVar, 4> labels;

            // walking over all corner placements
            for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

                // create 4 variables y that represent whether this corner was set
                int labelIdx = getLabelIdx(pointIdx, static_cast<Point::Corner>(corner));
                GRBVar y = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y_" + std::to_string(labelIdx));
                yVars.push_back(y);
                labels[corner] = y;
            
                // we cannot yet create the constraint, but we can store the indices for the constraint
                for(auto n : p->getNeighbours()) {

                    int otherPointIdx = n->getIdx();

                    for(int otherCorner = Point::TOP_LEFT; otherCorner != Point::NOT_PLACED; otherCorner++) {

                        int otherLabelIdx = getLabelIdx(otherPointIdx, static_cast<Point::Corner>(otherCorner));

                        if(Point::checkCollision(p->getCoordsForPlacement(static_cast<Point::Corner>(corner)), 
                                n->getCoordsForPlacement(static_cast<Point::Corner>(otherCorner)))) {

                            std::tuple<int, int> conflict = std::make_tuple(labelIdx, otherLabelIdx);
                            conflicts.push_back(conflict);
                        }
                    }
                }
            }

            // adding the constraint that a feature is only set if at least one label is set
            model.addConstr(x - labels[0] - labels[1] - labels[2] - labels[3] == 0, "label_"+std::to_string(pointIdx));
        
        }

        // adding the constraint that no two labels may overlap
        // TODO get rid of the doubled ones here: e.g. (3,7) vs. (7,3)
        for(auto tup : conflicts) {
            int first = std::get<0>(tup);
            int second = std::get<1>(tup);
            model.addConstr(yVars[first] + yVars[second] <= 1, 
                "overlap_" + std::to_string(first) + "_" + std::to_string(second));
        }

        model.setObjective(obj, GRB_MAXIMIZE);

        // ADDING CALLBACKS
        CustomCallback custom_cb(instance, model);
        model.setCallback(&custom_cb);

        // Optimize model
        model.optimize();

        int i = 0;
        for(GRBVar y : yVars) {
            
            if(y.get(GRB_DoubleAttr_X) == 1) {
                int idx = getPointIdxFromLabel(i);
                Point::Corner corner = getCornerFromLabel(i);
                solution.setLabel(idx, corner);
            }
            i++;
        }

        std::cout << "Final Objective Value: " << model.get(GRB_DoubleAttr_ObjVal) << std::endl;

    } catch(GRBException e) {
        std::cout << "Error code = " << e.getErrorCode() << std::endl;
        std::cout << e.getMessage() << std::endl;
    } catch(...) {
        std::cout << "Exception during optimization" << std::endl;
    }

    return solution;
}
