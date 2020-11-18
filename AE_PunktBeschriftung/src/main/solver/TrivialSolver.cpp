#include "solver/TrivialSolver.hpp"


// Walk over all points of the instance.
// For each, walk over all possible Corner placements
// For each, walk over all already set points and check for collisions
Solution TrivialSolver::solve(Instance& instance) const {

    Solution solution(instance);

    // set the label of the first point to top left
    solution.setLabel(0, Point::TOP_LEFT);

    // walking over all points
    for (int i = 0; i < instance.size(); ++i) {

        Point p = instance.getPoint(i);

        // walking over all corner placements
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // tracking whether we collided with one of them
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
                solution.setLabel(i, static_cast<Point::Corner>(corner));
                break; // no need to look at the remaining corner placements
            }
        }
    }

    return solution;
}
