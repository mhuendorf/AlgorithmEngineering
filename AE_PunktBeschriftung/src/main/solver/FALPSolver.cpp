#include <solver/FALPSolver.hpp>

#include <iostream>

FALPSolver::FALPSolver() : labelQ{this->labelCmp}, overlaps{} {

}

// calculates a unique ID for each label from pointIdx corner
int getLabelIdx(int pointIdx, Point::Corner corner) {
    return pointIdx * 4 + corner;
}

// calculates the Point-Index back from the labelIdx
int getPointIdxFromLabel(int labelIdx) {
    return (labelIdx - 1) / 4;
}

// calculates the corner back from the labelIdx
Point::Corner getCornerFromLabel(int labelIdx) {
    return static_cast<Point::Corner>( ( (labelIdx - 1) % 4 ) + 1 );
}

void FALPSolver::setupLabelQ(const Instance& instance) {

    // for all points
    for(const Point::Ptr& p : instance.getPoints()) {

        // for all label positions
        for(int corner = Point::TOP_LEFT; corner != Point::BOTTOM_RIGHT; corner++) {

            // int labelIdx = getLabelIdx((*p).getIdx(), static_cast<Point::Corner>(corner)); // not necessary
            std::list<int> overlapList;
            
            Point::Rectangle rect1 = (*p).getCoordsForPlacement(static_cast<Point::Corner>(corner));

            // counts the overlaps 
            int overlapCounter = 0;
            
            for( const Point::Ptr& neighbour : (*p).getNeighbours()) {

                for(int corner2 = Point::TOP_LEFT; corner2 != Point::BOTTOM_RIGHT; corner2++) {

                    Point::Rectangle rect2 = (*neighbour).getCoordsForPlacement(static_cast<Point::Corner>(corner2));
                    if( Point::checkCollision(rect1, rect2) ) {
                        overlapCounter++;
                        int otherLabelIdx = getLabelIdx((*neighbour).getIdx(), static_cast<Point::Corner>(corner2));
                        overlapList.push_back(otherLabelIdx);
                    }
                }
            }

            // this list migh be empty if we never overlapped,
            // otherwise it contains the label-indices of the labels we overlapped with
            // we can simply push back because our label-index is 0,1,2,3... automatically
            overlaps.push_back(overlapList);

            // glue these together and put them into the Q
            QElem elem((*p).getIdx(), static_cast<Point::Corner>(corner), overlapCounter);
            labelQ.push(elem);
        }
    }

}

Solution FALPSolver::solve(Instance& instance) {

    // step 1: put all labels into a priority queue, sorting by number of overlaps
    setupLabelQ(instance);

    // step 2: add the labels with lowest number of conflicts to the solution
    Solution solution(instance);
    while(!labelQ.empty()) 
    {
        QElem elem = labelQ.top();
        solution.setLabel(elem.idx, elem.corner);
        labelQ.pop();

        // step 3: remove all labels that we overlapped and decrease the labels that those overlapped
        
        
    }
    
    return solution;
}