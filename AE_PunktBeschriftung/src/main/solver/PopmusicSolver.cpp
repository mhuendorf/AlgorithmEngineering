#include <solver/PopmusicSolver.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/Utils.hpp>


BasicSolution PopmusicSolver::solve(Instance& instance) {

    // step 1: call trivial solver for initial solution
    TrivialSolver trivial;
    this->solution = trivial.solve(instance);

    // step 2: create list of overlaps
    setupOverlaps(instance);

    // step 3: start popmusic procedure
    std::set<int> waiting_list; // stores parts that still need to be tried - in the beginning, all nodes
    for(int idx = 0; idx < instance.size(); idx++) {
        waiting_list.insert(idx);
    }

    // while there are still nodes that need improvement
    while( !waiting_list.empty() ) {

        // creating the subproblem: r nodes in the direct or indirect neighbourhood of seed part
        int si = *waiting_list.begin(); // seed part
        Subproblem sub = createSubProblem(instance, subProblemSize, si);

        // start tabuSearch for this subproblem
        tabuSearch(sub);

        // remove the seed part from the waiting list
        // TODO make this conditional on whether something was changed
        waiting_list.erase(si);
    }

    return solution;
}

void PopmusicSolver::setupOverlaps(const Instance& instance) {

    // for all points
    for(const Point::Ptr& p : instance.getPoints()) {

        // for all label positions
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            std::vector<int> overlapList; // stores the indices of the labels with which this label overlaps
            overlapList.reserve((*p).getNeighbours().size() * 4); // reserving too much space, probably
            
            Point::Rectangle rect1 = (*p).getCoordsForPlacement(static_cast<Point::Corner>(corner));
            
            for( const Point::Ptr& neighbour : (*p).getNeighbours()) {

                for(int corner2 = Point::TOP_LEFT; corner2 != Point::NOT_PLACED; corner2++) {

                    Point::Rectangle rect2 = (*neighbour).getCoordsForPlacement(static_cast<Point::Corner>(corner2));
                    if( Point::checkCollision(rect1, rect2) ) {
                        int otherLabelIdx = getLabelIdx((*neighbour).getIdx(), static_cast<Point::Corner>(corner2));
                        overlapList.push_back(otherLabelIdx);
                    }
                }
            }

            // this list migh be empty if we never overlapped,
            // otherwise it contains the label-indices of the labels we overlapped with
            // we can simply push back because our label-index is 0,1,2,3... automatically if we iterate in this way
            overlapList.shrink_to_fit();
            this->overlaps.push_back(overlapList);
        }
    }
}

// creates a subproblem for instance of size r, at seed point si
Subproblem PopmusicSolver::createSubProblem(const Instance& instance, size_t r, int si) const {

    std::set<int> Q; // contains all nodes of the subgraph starting at si
    Q.insert(si);
    Subproblem sub; // contains Ri and Border

    // while the subproblem is not large enough and there are nodes left
    while( sub.Ri.size() < r && !Q.empty() ) {

        // take the first node from the Q and store it in Ri, remember that this is not a border point
        int x = *Q.begin();
        Q.erase(x);
        sub.Ri.insert(x);
        sub.border.insert(std::make_pair(x, false)); // they don't say this in the paper but this should be helpful

        // walk over all labels of that point
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

    // Ri is full now (or we ran out of points), but maybe Q has some left
    while(!Q.empty()) {
        int x = *Q.begin();
        Q.erase(x);
        sub.Ri.insert(x);
        // insert all those as border points
        sub.border.insert(std::make_pair(x, true));
    }

    return sub;
}

void PopmusicSolver::tabuSearch(const Subproblem& sub) {
    
    // copy of the solution with which we will be working
    BasicSolution localSolution = solution;

    // priority Q for labels (multiset because C++ Q sucks)
    // sorting labels by #overlaps
    struct compare {
        bool operator()(std::tuple<int, int> left, 
                        std::tuple<int, int> right) const {
            return std::get<1>(left) < std::get<1>(right);
        }
    };
    std::multiset< std::tuple<int, int>, compare > candidates; // stores labels as tuples of label-idx and #overlaps

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

    // if we have no candidates, return empty improvements
    if(candidates.size() == 0) {
        return;
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

            std::set<int> repairPoints; // indices of all points that need repair

            // For all labels that we overlap (generally, regardless of whether they are set or not)...
            for(int otherLabel : overlaps[labelIdx]) {
                
                int otherPointIdx = getPointIdxFromLabel(otherLabel);
                Point::Corner otherCorner = getCornerFromLabel(otherLabel);

                // ...if the point that we would cross is even in the solution and has that label placement...
                if(localSolution.contains(otherPointIdx) && localSolution.getCorner(otherPointIdx) == otherCorner) {
                    // ...then, delete that point and add it to the list of points that need to be repaired.
                    localSolution.resetLabel(otherPointIdx);
                    repairPoints.insert(otherPointIdx);
                }
            }

            // OVERVIEW: We will now repair all broken points.

            // TODO try all combinations here, or something crazy like that (maybe check how many there are, if it is too many, don't?)
            for(int brokenPointIdx : repairPoints) {

                Point p = instance.getPoint(brokenPointIdx);

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
            if(localSolution.size() >= solution.size()) {
                solution = localSolution;
            }

        } else {
            continue; // implicitly: go to next point
        }
    }
    // OVERVIEW: We tried to set new solutions for maxTabuIt many steps / while we still had candidates

    return;
}