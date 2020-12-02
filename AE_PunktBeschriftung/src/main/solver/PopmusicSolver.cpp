#include <solver/PopmusicSolver.hpp>
#include <solver/FALPSolver.hpp>
#include <solver/Utils.hpp>


BasicSolution PopmusicSolver::solve(Instance& instance) {

    // step 1: call FALPSolver for initial solution
    FALPSolver falp;
    this->solution = falp.solve(instance);

    //std::cout << "initial solving worked. Solution: " << solution << std::endl;

    // step 2: TODO copy overlaps from FALPSolver into this object - maybe not necessary, take them from falp
    this->overlaps = falp.getOverlaps();

    // step 3: start popmusic procedure
    std::set<int> waiting_list; // stores parts that still need to be tried - in the beginning, all nodes
    for(int idx = 0; idx < instance.size(); idx++) {
        waiting_list.insert(idx);
    }

    // while there are still nodes that need improvement
    while( !waiting_list.empty() ) {

        // creating the subproblem: r nodes in the direct or indirect neighbourhood of seed part
        int si = *waiting_list.begin(); // seed part
        int r = 20;
        Subproblem sub = createSubProblem(instance, r, si);

        //std::cout << "Subproblem creation worked: " << std::endl;
        // for(int node : sub.Ri) {
        //     std::cout << node << std::endl;
        // }

        std::map<int, Point::Corner> improvements = tabuSearch(sub);

        //std::cout << "TabuSearch complete. Improvements: " << std::endl;
        // for(auto prIt = improvements.begin(); prIt != improvements.end(); prIt++) {
        //     std::cout << prIt->first << " " << prIt->second << std::endl;
        // }

        if(!improvements.empty()) {

            // mark all of those points as candidate for improvement again
            for(auto it = sub.Ri.begin(); it != sub.Ri.end(); it++) {
                waiting_list.insert(*it);
            }

            // realize all those improvements
            for(auto it = improvements.begin(); it != improvements.end(); it++) {
                int pointIdx = it->first;
                Point::Corner corner = it->second;
                solution.setLabel(pointIdx, corner);
            }

        } else {
            waiting_list.erase(si);
        }
    }

    return solution;
}

Subproblem PopmusicSolver::createSubProblem(const Instance& instance, int r, int si) const {

    std::set<int> Q;
    Q.insert(si);
    Subproblem sub; // contains Ri and Border

    while( sub.Ri.size() < r && !Q.empty() ) {

        int x = *Q.begin();
        Q.erase(x);
        sub.Ri.insert(x);
        sub.border.insert(std::make_pair(x, false)); // they don't say this in the paper but this should be helpful

        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // get label index for x and the chosen corner
            int k = getLabelIdx(x, static_cast<Point::Corner>(corner));

            for(int j : overlaps[k]) {
                int p = getPointIdxFromLabel(j);
                // for all labels that k overlaps, 
                // check if their points are neither in Ri nor in Q
                // if so, insert p into Q: this point is a candidate
                if(sub.Ri.find(p) == sub.Ri.end() && Q.find(p) == Q.end()) {
                    Q.insert(p);
                }
            }
        }
    }

    while(!Q.empty()) {
        int x = *Q.begin();
        Q.erase(x);
        sub.Ri.insert(x);
        sub.border.insert(std::make_pair(x, true));
    }

    return sub;
}

std::map<int, Point::Corner> PopmusicSolver::tabuSearch(const Subproblem& sub) {
    
    // setup

    BasicSolution localSolution = solution;

    std::map<int, Point::Corner> improvements; // map to store improvements in

    // priority Q for labels (multiset because C++ Q sucks)
    struct compare {
        bool operator()(std::tuple<int, int> left, 
                        std::tuple<int, int> right) const {
            return std::get<1>(left) < std::get<1>(right);
        }
    };
    std::multiset< Point::Point2D, compare > candidates; // maps label-index to #overlaps of that label

    //std::cout << "Made it past candidate init, #candidates: " << candidates.size() << std::endl;

    // maps node-indices to number of iterations in which this node may not be changed
    std::map<int, int> tabuList; // if the value of a node is < 0, we are allowed to change it

    // for all nodes in the subproblem
    for(int idx : sub.Ri) {

        // tabu status is -1 for all nodes in the beginning, meaning we can change all of them,
        // unless they are in border TODO check if they are in border
        tabuList.insert(std::make_pair(idx, -1)); 

        // collect all indices of nodes that are not set
        if(!localSolution.contains(idx)) {
            for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                int labelIdx = getLabelIdx(idx, static_cast<Point::Corner>(corner));
                std::tuple<int, int> tup( labelIdx, overlaps[labelIdx].size() ); // TODO maybe use the actual number of overlaps here, not the theoretical maximum
                candidates.insert( tup );
            }
        }

    }
    int iterations = 0;

    //std::cout << "Made it through TS init, #candidate-labels: " << candidates.size() << std::endl;

    // TODO make this more efficient
    // if we have no candidates, return empty improvements
    if(candidates.size() == 0) {
        //std::cout << "Returning empty improvements" << std::endl;
        return improvements;
    }

    // end of setup
    
    // while not done, select cheapest candidate from list
    while( iterations < this->maxTabuIt && !candidates.empty() ) {
        iterations++;

        // retrieving a candidate: a not-yet-set label with lowest number of overlaps
        std::tuple<int, int> candidate = *candidates.begin();
        candidates.erase(candidates.begin());

        // parsing the label into point and corner
        int labelIdx = std::get<0>(candidate);
        int pointIdx = getPointIdxFromLabel(labelIdx);
        Point::Corner corner = getCornerFromLabel(labelIdx);

        // If we are allowed to set that point, we do it
        if(tabuList[pointIdx] < 0) {

            tabuList[pointIdx] = tenure; // not allowed to touch this point anymore from now on

            localSolution.setLabel(pointIdx, corner);

            // OVERVIEW: we will now have to repair all points that clash with the new label

            std::set<int> repairPoints;

            // For all labels that we overlap (generally, regardless of whether they are set or not)...
            for(int otherLabel : overlaps[labelIdx]) {
                //std::cout << "Crossing other label: " << otherLabel << " for point: " << getPointIdxFromLabel(otherLabel) <<  " and label: " << getCornerFromLabel(otherLabel) <<  std::endl;
                
                int otherPointIdx = getPointIdxFromLabel(otherLabel);
                Point::Corner otherCorner = getCornerFromLabel(otherLabel);

                // ...if the point that we would cross is even in the solution and has that label placement...
                if(localSolution.contains(otherPointIdx) && localSolution.getCorner(otherPointIdx) == otherCorner) {
                    // ...then, delete that point and add it to the list of points that need to be repaired.
                    //std::cout << "We actually hit that one, removing " << otherPointIdx << std::endl;
                    localSolution.resetLabel(otherPointIdx);
                    repairPoints.insert(otherPointIdx);
                }
            }
            // std::cout << "All Repair Points have succesfully been set! RepairPoints size: " << repairPoints.size() << std::endl;
            // for(int rep : repairPoints) {
            //     std::cout << rep << std::endl;
            // }

            // OVERVIEW: We will now repair all broken points.

            // TODO try all combinations here, or something crazy like that (maybe check how many there are, if it is too many, don't?)
            for(int brokenPointIdx : repairPoints) {

                //std::cout << "Trying to re-set: " << brokenPointIdx << std::endl;

                Point p = instance.getPoint(brokenPointIdx);
                // Todo this should really be a util-method somewhere
                for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                    
                    // tracking whether we collided with one of the neighbours
                    bool collided = false;

                    // walking over all neighbours of the point to check for collisions
                    for(const Point::Ptr& other : p.getNeighbours()) {

                        // if they collide, note that and stop checking the others
                        if(localSolution.checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                            collided = true;
                            break;
                        } 
                    }
                    
                    // if we never collided, set the label
                    if(!collided) {
                        localSolution.setLabel(brokenPointIdx, static_cast<Point::Corner>(corner));
                        break; // no need to look at the remaining corner placements
                    }
                }
            }

            // OVERVIEW: We chose a candidate label, set that, tried to repair all the nodes that were broken and will now do this for the next candidate
            
            // If that actually improved the solution, we will set it now
            //std::cout << "old Solution: " << solution.size() << ", new Solution: " << localSolution.size() << std::endl;
            if(localSolution.size() >= solution.size()) {
                solution = localSolution;
            }

        } else {
            continue; // implicitly: go to next point
        }
    }
    // OVERVIEW: We tried to set new solutions for maxTabuIt many steps / while we still had candidates

    return improvements;
}