#include <solver/FALPSolver.hpp>

#include <iostream>

FALPSolver::FALPSolver() : labelQ{this->labelCmp}, overlaps{} {}

// calculates a unique ID for each label from pointIdx corner
int getLabelIdx(int pointIdx, Point::Corner corner) {
    return pointIdx * 4 + corner;
}

// calculates the Point-Index back from the labelIdx
int getPointIdxFromLabel(int labelIdx) {
    return labelIdx / 4;
}

// calculates the corner back from the labelIdx
Point::Corner getCornerFromLabel(int labelIdx) {
    return static_cast<Point::Corner>( labelIdx % 4 );
}

// prints labelQ for debugging
void FALPSolver::printSet() {
    for(QElem e : labelQ) {
        std::cout << e.overlaps << " " << e.idx << " " << e.corner << std::endl;
    }
}

void FALPSolver::setupLabelQ(const Instance& instance) {

    // for all points
    for(const Point::Ptr& p : instance.getPoints()) {

        // for all label positions
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // int labelIdx = getLabelIdx((*p).getIdx(), static_cast<Point::Corner>(corner)); // not necessary
            std::vector<int> overlapList;
            overlapList.reserve((*p).getNeighbours().size() * 4); // reserving too much space, probably
            
            Point::Rectangle rect1 = (*p).getCoordsForPlacement(static_cast<Point::Corner>(corner));

            // counts the overlaps 
            int overlapCounter = 0;
            
            for( const Point::Ptr& neighbour : (*p).getNeighbours()) {

                for(int corner2 = Point::TOP_LEFT; corner2 != Point::NOT_PLACED; corner2++) {

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
            overlapList.shrink_to_fit();
            overlaps.push_back(overlapList);

            // glue these together and put them into the Q
            QElem elem((*p).getIdx(), static_cast<Point::Corner>(corner), overlapCounter);
            labelQ.insert(elem);
        }
    }
}

void FALPSolver::setBestLabels(Solution& solution) {
    std::set<int> deleted;
    //std::cout << "LabelQ in the beginning: " << std::endl;
    //printSet();
    while(!labelQ.empty()) {

        QElem elem = *labelQ.begin();
        //std::cout << "Setting " << elem.idx << " " << elem.corner << std::endl;

        // set this label in the solution and remove it from the labelQ
        solution.setLabel(elem.idx, elem.corner);
        labelQ.erase(labelQ.begin());
        
        int labelIdx = getLabelIdx(elem.idx, elem.corner);
        // remove all labels that elem overlapped and decrease the labels that those overlap
        for(const int& v : overlaps[labelIdx]) {
            //std::cout << "Deleting overlap: " << getPointIdxFromLabel(v) << " " << getCornerFromLabel(v) << std::endl;

            // making sure not to delete twice
            auto search = deleted.find(v);
            if(search != deleted.end()) {
                // we already deleted this one, continue with next one
                continue;
            }

            // removing v from L by first defining a search target, finding and erasing it
            // TODO this is a huge problem in this implementation: C++ does not have the magical datastructure they propose,
            // so we actually have to search in linear time here
            std::multiset<QElem>::iterator it = labelQ.begin();
            QElem target = QElem(getPointIdxFromLabel(v), getCornerFromLabel(v), 0);

            while(it != labelQ.end()) {
                if(*it == target) {
                    labelQ.erase(it);
                    deleted.insert(v); // consider it deleted next time
                    break;
                }
                it++;
            }

            // decrementing the conflict count for all labels that were overlapped by v
            for(const int& w : overlaps[v]) {

                //std::cout << "Decrementing counter of " << getPointIdxFromLabel(w) << " " << getCornerFromLabel(w) << std::endl;

                // again, checking if this one even needs to be considered
                auto search = deleted.find(w);
                if(search != deleted.end()) {
                    // we already deleted this one
                    continue;
                }

                //std::cout << "Actually has to do something here" << std::endl;

                std::multiset<QElem>::iterator it2 = labelQ.begin();
                QElem target2 = QElem(getPointIdxFromLabel(w), getCornerFromLabel(w), 0);

                while(it2 != labelQ.end()) {
                    if(*it2 == target2) {
                        QElem updated = *it2; // implicit call to copy constructor
                        updated.overlaps -= 1;
                        labelQ.erase(it2); 
                        labelQ.insert(updated);
                        break;
                    }
                it2++;
                }
            }
            //printSet();
        }
    }
}

Solution FALPSolver::solve(Instance& instance) {

    // creating solution to store results in
    Solution solution(instance);

    // put all labels into a priority Q, sorting by number of overlaps
    setupLabelQ(instance);

    // step 1: iteratively pull labels with least overlaps from Q
    setBestLabels(solution);

    // step 2: I think this might actually be superfluous here!
    // TODO benchmark FALPSolver against TrivialSolver

    
    return solution;
}