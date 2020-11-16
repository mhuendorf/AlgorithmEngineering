#include <representations/SimpleSolution.hpp>
#include "solver/TrivialSolver.hpp"


// Walk over all points of the instance.
// For each, walk over all possible Corner placements
// For each, walk over all already set points and check for collisions
SimpleSolution &TrivialSolver::solve(Instance &instance) const {

    SimpleSolution solution(instance);
    // walking over all points
    for (int i = 0; i < instance.size(); ++i) {

        Point p = solution.getPoint(i);

        if (solution.getLabelledPoints().empty()) {
            solution.setLabel(i, Point::TOP_LEFT);
            continue;
        }

        // walking over all corner placements
        for (int corner = Point::TOP_LEFT; corner != Point::BOTTOM_RIGHT; corner++) {

            // tracking whether we collided with one of them
            bool collided = false;

            // walking over all set points
            for (int otherIdx : solution.getLabelledPoints()) {

                // if they collide, note that and stop checking the others
                if (instance.getPoint(otherIdx).checkCollision(p, static_cast<Point::Corner>(corner))) {
                    collided = true;
                    break;
                }
            }

            // if we never collided, set the label
            if (!collided) {
                solution.setLabel(i, static_cast<Point::Corner>(corner));
                break; // no need to look at the remaining corner placements
            }
        }
    }
    return solution;
}
