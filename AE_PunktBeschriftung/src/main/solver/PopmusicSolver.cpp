#include <solver/PopmusicSolver.hpp>
#include <solver/FALPSolver.hpp>
#include <solver/Utils.hpp>

#include <list>

Solution PopmusicSolver::solve(Instance& instance) {

    // step 1: call FALPSolver for initial solution
    FALPSolver falp;
    this->solution = falp.solve(instance);

    // step 2: TODO copy overlaps from FALPSolver into this object - maybe not necessary, take them from falp

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

        std::map<int, Point::Corner> improvements = tabuSearch(sub);
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

    std::map<int, Point::Corner> improvements; // map to store improvements in
    
    // priority Q for labels
    std::function<bool(std::tuple<int, int>, std::tuple<int, int>)> comparison = [](std::tuple<int, int> left, std::tuple<int, int> right) { return std::get<1>(left) < std::get<1>(right); }; // TODO check if this is the right way around
    std::priority_queue<std::tuple<int, int>, std::vector< std::tuple<int, int> >, decltype(comparison)> candidates; // maps label-index to #overlaps of that label

    // maps node-indices to number of iterations in which this node may not be changed
    std::map<int, int> tabuList; // if the value of a node is < 0, we are allowed to change it

    // for all nodes in the subproblem
    for(int idx : sub.Ri) {

        // tabu status is -1 for all nodes in the beginning, meaning we can change all of them,
        // unless they are in border TODO check if they are in border
        tabuList.insert(std::make_pair(idx, -1)); 

        // collect all indices of nodes that are not set
        if(!solution.contains(idx)) {
            for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                int labelIdx = getLabelIdx(idx, static_cast<Point::Corner>(corner));
                candidates.push(std::tuple<int, int>(labelIdx, overlaps[labelIdx].size()));
            }
        }

    }
    int iterations = 0;

    // TODO make this more efficient
    // if we have no candidates, return empty improvements
    if(candidates.size() == 0) {
        return improvements;
    }

    // end of setup
    
    // while not done, select cheapest candidate from list, set that label, 
    while(iterations < this->maxTabuIt) {
        iterations++;

        // retrieving a candidate: a not-yet-set label with lowest number of overlaps
        std::tuple<int, int> candidate = candidates.top();
        candidates.pop();
        int labelIdx = std::get<0>(candidate);

        // setting that label
        int pointIdx = getPointIdxFromLabel(labelIdx);

        if(tabuList[pointIdx] < 0) {

            std::vector<int> repairPoints;
            Point::Corner corner = getCornerFromLabel(labelIdx);

            solution.setLabel(pointIdx, corner);

            // this label possibly overlaps with something else - if so, remove that other label
            for(int otherLabel : overlaps[labelIdx]) {
                int otherPointIdx = getPointIdxFromLabel(otherLabel);
                if(solution.contains(otherPointIdx)) {
                    Point::Corner otherCorner = solution.getCorner(otherPointIdx);
                    Point::Corner badCorner = getCornerFromLabel(labelIdx);
                    if(otherCorner == badCorner) {
                        solution.resetLabel(otherPointIdx);
                        repairPoints.push_back(otherPointIdx);
                    }
                }
            }

            // now try to repair all of those broken points 
            // TODO try all combinations here, or something crazy like that (maybe check how many there are, if it is too many, don't?)
            for(auto it = repairPoints.begin(); it != repairPoints.end(); it++) {
                int brokenPointIdx = *it;
                Point p = instance.getPoint(brokenPointIdx);
                // Todo this should really be a util-method somewhere
                for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                    
                    // tracking whether we collided with one of the neighbours
                    bool collided = false;

                    // walking over all neighbours of the point to check for collisions
                    for(const Point::Ptr& other : p.getNeighbours()) {

                        // if they collide, note that and stop checking the others
                        if(solution.checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                            collided = true;
                            break;
                        } 
                        
                    }
                    
                    // if we never collided, set the label
                    if(!collided) {
                        solution.setLabel(brokenPointIdx, static_cast<Point::Corner>(corner));
                        repairPoints.erase(it);
                        break; // no need to look at the remaining corner placements
                    }
                }
            }

        } else {
            continue; // implicitly: go to next point
        }
    }

    return improvements;
}