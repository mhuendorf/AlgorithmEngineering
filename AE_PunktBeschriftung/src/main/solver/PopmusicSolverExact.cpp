#include <solver/PopmusicSolverExact.hpp>
#include <solver/TrivialSolver.hpp>
#include <solver/Utils.hpp>


BasicSolution PopmusicSolverExact::solve(Instance& instance) {

    // step 1: call trivial solver for initial solution
    TrivialSolver trivial;
    this->solution = trivial.solve(instance);

    // step 2: create list of overlaps
    setupOverlaps(instance);

    // step 3: start popmusic procedure
    for(int idx = 0; idx < instance.size(); idx++) {

        // creating the subproblem: r nodes in the direct or indirect neighbourhood of seed part
        Subproblem sub = createSubProblem(instance, subProblemSize, idx);

        // start tabuSearch for this subproblem
        tabuSearch(sub);

    }

    return solution;
}

void PopmusicSolverExact::setupOverlaps(const Instance& instance) {

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
Subproblem PopmusicSolverExact::createSubProblem(const Instance& instance, size_t r, int si) const {

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

void PopmusicSolverExact::tabuSearch(const Subproblem& sub) {

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
        if(!solution.contains(idx)) {
            for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {
                int labelIdx = getLabelIdx(idx, static_cast<Point::Corner>(corner));
                std::tuple<int, int> tup( labelIdx, overlaps[labelIdx].size() ); // TODO maybe use the actual number of overlaps here, not the theoretical maximum
                candidates.insert( tup );
            }
        }
    }
    int iterations = 0;

    // size of candidates is usually 20 - 80
    // if we have no candidates, abort
    if(candidates.size() == 0) {
        return;
    }
    // end of setup

    this->maxTabuIt = candidates.size() * 1.5;
    // while not done, select cheapest candidate from list
    while( iterations < this->maxTabuIt && !candidates.empty() ) {
        iterations++;

        // storing the current value of the solution
        int bestSolution = solution.size();

        // for storing the current values of all labels we want to set
        std::vector<std::tuple<int, Point::Corner>> labelMemory;

        // retrieving a candidate: a not-yet-set label with lowest number of overlaps
        std::tuple<int, int> candidate = *candidates.begin();

        // parsing the label into point and corner
        int labelIdx = std::get<0>(candidate);
        int pointIdx = getPointIdxFromLabel(labelIdx);
        Point::Corner corner = getCornerFromLabel(labelIdx);

        // If we are allowed to set that point, we do it
        if(tabuList[pointIdx] < 0) {

            candidates.erase(candidates.begin());

            tabuList[pointIdx] = tenure; // not allowed to touch this point anymore from now on

            labelMemory.push_back({pointIdx, solution.getCorner(pointIdx)}); // make a backup
            solution.setLabel(pointIdx, corner);

            // OVERVIEW: we will now have to repair all points that clash with the new label

            std::set<int> repairPoints; // indices of all points that need repair

            // For all labels that we overlap (generally, regardless of whether they are set or not)...
            for(int otherLabel : overlaps[labelIdx]) {

                int otherPointIdx = getPointIdxFromLabel(otherLabel);
                Point::Corner otherCorner = getCornerFromLabel(otherLabel);

                // ...if the point that we would cross is even in the solution and has that label placement...
                if(solution.contains(otherPointIdx) && solution.getCorner(otherPointIdx) == otherCorner) {
                    // ...then, delete that point and add it to the list of points that need to be repaired.
                    labelMemory.push_back({otherPointIdx, solution.getCorner(otherPointIdx)});
                    solution.resetLabel(otherPointIdx);
                    repairPoints.insert(otherPointIdx);
                }
            }

            // OVERVIEW: We will now repair all broken points.
            const int MAX_REPAIR_POINTS_OPTIMAL = 6;

            //split points into trivial and none trivial points
            std::vector<int> notTrivialPoints;
            std::vector<int> trivialPoints;

            //for all points to repair
            for (int brokenPointIdx : repairPoints) {
                //if too big to handle all combinations break early
                if (notTrivialPoints.size() > MAX_REPAIR_POINTS_OPTIMAL) {
                    break;
                }
                //get its neighbors
                bool isTrivial = false;
                for (const Point::Ptr &neighbor : solution.getPoint(brokenPointIdx).getNeighbours()) {
                    //and check if they are in the list of points to fix
                    if (std::find(repairPoints.begin(), repairPoints.end(), neighbor->getIdx()) !=
                        repairPoints.end()) {
                        notTrivialPoints.push_back(brokenPointIdx);
                        isTrivial = true;
                        break;
                    }
                }
                if (!isTrivial) {
                    trivialPoints.push_back(brokenPointIdx);
                }
            }

            // try all combinations if number of Points to repair is small enough
            if (notTrivialPoints.size() <= MAX_REPAIR_POINTS_OPTIMAL && !notTrivialPoints.empty()) {

                std::vector<int> bestCombo(notTrivialPoints.size());
                int bestScore = -1;
                int numCombinations = pow(5, notTrivialPoints.size());
                for (int i = 0; i < numCombinations; ++i) {
                    int comboId = i;
                    int possibleScore = 0;
                    std::vector<int> combo(notTrivialPoints.size());
                    combo.clear();
                    while (comboId > 0) {
                        combo.push_back(comboId % 5);
                        if (Point::Corner::NOT_PLACED != static_cast<Point::Corner>(combo.at(combo.size()-1))) {
                            possibleScore++;
                        }
                        comboId /= 5;
                    }
                    while (combo.size() < notTrivialPoints.size()) {
                        combo.push_back(0);
                    }

                    //a combination has been generated, now test it
                    int j = 0;

                    bool collided = false;
                    for (int brokenPointIdx : notTrivialPoints) {
                        solution.setLabel(brokenPointIdx, static_cast<Point::Corner>(combo.at(j)));
                        Point p = instance.getPoint(brokenPointIdx);
                        // walking over all neighbours of the point to check for collisions
                        for (const Point::Ptr &other : p.getNeighbours()) {
                            // if they collide, note that and stop checking the others
                            if (solution.checkCollision(p, static_cast<Point::Corner>(combo.at(j)), (*other).getIdx())) {
                                collided = true;
                                break;
                            }
                        }
                        if (collided == true)
                            break;
                        j++;
                    }
                    if (!collided && possibleScore > bestScore) {
                        bestScore = possibleScore;
                        bestCombo.clear();
                        for (int k : combo) {
                            bestCombo.push_back(k);
                        }
                    }
                }

                //best combination has been found... set it once again
                int i = 0;
                for (int brokenPointIdx : notTrivialPoints) {
                    solution.setLabel(brokenPointIdx, static_cast<Point::Corner>(bestCombo.at(i)));
                    i++;
                }

                //if too much combinations to handle set trivial Points to all points
            } else if (notTrivialPoints.size() > MAX_REPAIR_POINTS_OPTIMAL) {
                trivialPoints.clear();
                for (int idx : repairPoints)
                    trivialPoints.push_back(idx);
            }

            for (int brokenPointIdx : trivialPoints) {

                Point p = instance.getPoint(brokenPointIdx);

                for (int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

                    // tracking whether we collided with one of the neighbours
                    bool collided = false;

                    // walking over all neighbours of the point to check for collisions
                    for (const Point::Ptr &other : p.getNeighbours()) {

                        // if they collide, note that and stop checking the others
                        if (solution.checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                            collided = true;
                            break;
                        }
                    }

                    // if we never collided, set the label
                    if (!collided) {
                        solution.setLabel(brokenPointIdx, static_cast<Point::Corner>(corner));
                        break; // no need to look at the remaining corner placements
                    }
                }
            }

            // OVERVIEW: We chose a candidate label, set that, tried to repair all the nodes that were broken and will now do this for the next candidate
            
            // If that actually improved the solution, we will set it now
            if(solution.size() >= bestSolution) {
                // don't worry, be happy
            } else {
                // start time machine (don't tell the ministry of magic)
                for(auto tup : labelMemory) {
                    solution.setLabel(std::get<0>(tup), std::get<1>(tup));
                }
            }

        } else {
            tabuList[pointIdx] -= 1; // trying to make this point possible
            continue; // implicitly: go to next point
        }
    }
    // OVERVIEW: We tried to set new solutions for maxTabuIt many steps / while we still had candidates
}