#include <random>
#include <iostream>
#include <solver/TrivialSolver.hpp>
#include "representations/SimulatedAnnealingSolution.hpp"

SimulatedAnnealingSolution::SimulatedAnnealingSolution(Instance& instance) : BasicSolution(instance), solutionScore(0), overlaps(instance.size()){

}

void SimulatedAnnealingSolution::initSolution() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(1, 4);
    for (int i = 0; i < instance->size(); ++i) {
        const Point& p = instance->getPoint(i);

        bool placed = false;
        // walking over all corner placements
        for(int corner = Point::TOP_LEFT; corner != Point::NOT_PLACED; corner++) {

            // tracking whether we collided with one of them
            bool collided = false;

            // walking over all neighbours of the point to check for collisions
            for(const Point::Ptr& other : p.getNeighbours()) {

                // if they collide, note that and stop checking the others
                if(checkCollision(p, static_cast<Point::Corner>(corner), (*other).getIdx())) {
                    collided = true;
                    break;
                }

            }

            // if we never collided, set the label
            if(!collided) {
                setLabel(i, static_cast<Point::Corner>(corner));
                placed = true;
                break; // no need to look at the remaining corner placements
            }
        }

        if (!placed) {
            Point::Corner corner;
            switch (dist(mt)) {
                case 1: {
                    corner = Point::TOP_LEFT;
                    break;
                }
                case 2: {
                    corner = Point::TOP_RIGHT;
                    break;
                }
                case 3: {
                    corner = Point::BOTTOM_LEFT;
                    break;
                }
                case 4: {
                    corner = Point::BOTTOM_RIGHT;
                }
            }

            this->setLabel(i, corner);
            Point other = this->getPoint(i);
            for (const auto &point : this->instance->getPoint(i).getNeighbours()) {
                if (this->checkCollision(other, corner, point->getIdx())) {
                    overlaps[i].push_back(point->getIdx());
                    overlaps[point->getIdx()].push_back(i);
                }
            }
        }
    }
    solutionScore = 0;
    for (auto & overlap : overlaps) {
        solutionScore += getPointScore(overlap.size());
    }
}

Point::Corner SimulatedAnnealingSolution::getCornerPlacement(int pointIdx) {
    Point p = getPoint(pointIdx);
    Point::Rectangle rect = placements.at(pointIdx);
    Point::Point2D topLeft = std::get<0>(rect);
    Point::Corner currPlacement;
    if (std::get<0>(topLeft) == p.getX()) {
        if (std::get<1>(topLeft) == p.getY()) {
            currPlacement = Point::Corner::TOP_LEFT;
        } else {
            currPlacement = Point::Corner::BOTTOM_LEFT;
        }
    } else {
        if (std::get<1>(topLeft) == p.getY()) {
            currPlacement = Point::Corner::TOP_RIGHT;
        } else {
            currPlacement = Point::Corner::BOTTOM_RIGHT;
        }
    }
    return currPlacement;
}

void SimulatedAnnealingSolution::changePlacement(int pointIdx, int randomNumber) {
    Point::Corner currPlacement = getCornerPlacement(pointIdx);
    randomNumber %= 3;
    randomNumber += 1;
    auto c = Point::Corner(randomNumber);
    if (c == currPlacement) {
        randomNumber += 1;
        if (randomNumber > Point::Corner::BOTTOM_RIGHT) {
            randomNumber = 1;
        }
        c = Point::Corner(randomNumber);
    }
    Point::Rectangle placement = getPoint(pointIdx).getCoordsForPlacement(c);
    placements.at(pointIdx) = placement;

    Point modifiedPoint = getPoint(pointIdx);
    solutionScore -= getPointScore(overlaps[pointIdx].size());

    // erase all overlaps with previous rects and reduce solution score accordingly
    for (int i = 0; i < overlaps[pointIdx].size(); ++i) {
        int toRemovePointIdx = overlaps[pointIdx][i];
        std::vector<int>* pointsVec = &overlaps[toRemovePointIdx];
        pointsVec->erase(std::remove(pointsVec->begin(), pointsVec->end(), pointIdx));
        solutionScore = solutionScore - getPointScore(pointsVec->size()+1) + getPointScore(pointsVec->size());
    }
    overlaps[pointIdx].clear();

    for (const auto& point : modifiedPoint.getNeighbours()) {
        if (this->checkCollision(modifiedPoint, c, point->getIdx())) {
            overlaps[pointIdx].push_back(point->getIdx());
            overlaps[point->getIdx()].push_back(pointIdx);
            solutionScore = solutionScore - getPointScore(overlaps[point->getIdx()].size()-1) + getPointScore(overlaps[point->getIdx()].size());
        }
    }
    solutionScore += getPointScore(overlaps[pointIdx].size());
}

double SimulatedAnnealingSolution::getPointScore(int numOverlaps) {
    return log(numOverlaps*exp(1)+1);
}

void SimulatedAnnealingSolution::printSolution(std::ostream &ostream) {
    ostream << this->instance->size() << "\n";
    for (int i = 0; i < this->instance->size(); ++i) {

        ostream << this->instance->getPoint(i);

        auto finder = this->placements.find(i);
        if(this->placements.end() != finder) {
            Point::Point2D rectCorner = std::get<0>(finder->second);
            ostream << "1 " << std::get<0>(rectCorner) << " " << std::get<1>(rectCorner);
        } else {
            ostream << "0 0 0";
        }
        ostream << "\t ";
        for (auto pointIdx : overlaps[i]) {
            ostream << pointIdx << ", ";
        }
        ostream << std::endl;
    }
    ostream << computeSolutionScore() << std::endl;
}

double SimulatedAnnealingSolution::computeSolutionScore() {
    double score = 0;
    for (const auto& points : overlaps) {
        score += getPointScore(points.size());
    }
    return score;
}

double SimulatedAnnealingSolution::getSolutionScore() const {
    return solutionScore;
}

void SimulatedAnnealingSolution::fixSolution() {
    std::cout << "start fixing..." << std::endl;
    if (solutionScore == 0) return;

    std::tuple<int, int> toFix(-1, -1);
    do {
        toFix = std::tuple<int, int>(-1, -1);
        for (int i = 0; i < overlaps.size(); ++i) {
            if (int(overlaps[i].size()) > std::get<1>(toFix)) {
                toFix = std::tuple<int, int>(i, overlaps[i].size());
            }
        }

        int removeIdx = std::get<0>(toFix);
        placements.erase(removeIdx);
        for (auto collision : overlaps[removeIdx]) {
            std::vector<int>* pointsVec = &overlaps[collision];
            pointsVec->erase(std::remove(pointsVec->begin(), pointsVec->end(), removeIdx));
        }
        overlaps[removeIdx].clear();
    } while (std::get<1>(toFix) > 0);
}
