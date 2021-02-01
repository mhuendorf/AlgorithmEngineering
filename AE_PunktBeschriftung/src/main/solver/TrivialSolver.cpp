#include <solver/TrivialSolver.hpp>
#include <solver/Utils.hpp>

#include <iostream>
#include <set>

// Walk over all points of the instance.
// For each, walk over all possible Corner placements
// For each, walk over all already set points and check for collisions
BasicSolution TrivialSolver::solve(Instance& instance) {

    BasicSolution solution(instance);

    // set the label of the first point to top left
    solution.setLabel(0, Point::TOP_LEFT);

    // walking over all points
    for (int i = 0; i < instance.size(); ++i) {

        const Point& p = instance.getPoint(i);

        // walking over all corner placements
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // tracking whether we collided with one of them
            bool collided = false;

            // walking over all neighbours of the point to check for collisions
            for(const Point* other : p.getNeighbours()) {

                // if they collide, note that and stop checking the others
                if(solution.checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                    collided = true;
                    break;
                } 
                
            }
            
            // if we never collided, set the label
            if(!collided) {
                solution.setLabel(i, static_cast<Point::Corner>(corner));
                break; // no need to look at the remaining corner placements
            }
        }
    }

    return solution;
}

// values is a vector of label indices of the labels that are supposed to be set, if possible
BasicSolution TrivialSolver::solve(Instance& instance, const std::vector<int>& values) {

    // std::cout << "Receiving " << values.size() << " suggestions." << std::endl;

    BasicSolution solution(instance);

    std::set<int> labelled;

    // walking over the suggested values
    for(auto it = values.begin(); it != values.end(); it++) {
        int pointIdx = getPointIdxFromLabel(*it);
        Point::Corner corner = getCornerFromLabel(*it);

        // verify that this point can actually be set
        const Point& p = instance.getPoint(pointIdx);
        bool collided = false;
        for(auto neigh = p.getNeighbours().begin(); neigh != p.getNeighbours().end(); neigh++) {
            if(solution.checkCollision(p, corner, (*(*neigh)).getIdx())) {
                collided = true;
                break;
            } 
        }

        // if we never collided, set this label
        if(!collided && !solution.contains(pointIdx)) {
            solution.setLabel(pointIdx, corner);
            labelled.insert(pointIdx);
        }

    }

    // now, greedily set the labels of all points that have not been labelled by suggestion
    for (int i = 0; i < instance.size(); i++) {

        // skip labelled points
        if(labelled.find(i) != labelled.end()) {
            continue;
        }

        const Point& p = instance.getPoint(i);

        // walking over all corner placements
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // tracking whether we collided with one of them
            bool collided = false;

            // walking over all neighbours of the point to check for collisions
            for(const Point* other : p.getNeighbours()) {

                // if they collide, note that and stop checking the others
                if(solution.checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                    collided = true;
                    break;
                } 
                
            }
            
            // if we never collided, set the label
            if(!collided) {
                solution.setLabel(i, static_cast<Point::Corner>(corner));
                break; // no need to look at the remaining corner placements
            }
        }
    }

    return solution;
}
