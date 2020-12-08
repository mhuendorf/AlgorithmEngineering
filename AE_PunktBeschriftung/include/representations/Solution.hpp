#ifndef LABEL_MAP_SOLUTION_HPP
#define LABEL_MAP_SOLUTION_HPP


#include <representations/Instance.hpp>

class Solution {

protected:
    const Instance& instance;

public:

    /**
     * Function to print a solution to an out stream.
     *
     * @param ostream the stream to be printed to
     */
    virtual void printSolution(std::ostream &ostream) = 0;

    /**
     * Constructor
     * @param instance1
     */
    explicit Solution(const Instance& instance);

    /**
     * Checks if the current state of the solution is feasible.
     * @return true if the solution is feasible, false else
     */
    [[nodiscard]] virtual bool isFeasible() const = 0;

    /**
     * Sets a label for a given Point.
     *
     * @param idx the index of the point
     * @param corner the corner, where the label is placed at
     */
    virtual void setLabel(int idx, Point::Corner corner) = 0;

    /**
     * Returns a point by its index.
     * @param idx the index of the point
     *
     * @return the point itself
     */
    [[nodiscard]] const Point& getPoint(int idx) const;

    /**
     * Checks how many labels are placed.
     *
     * @return the number of placed labels
     */
    [[nodiscard]] virtual int size() const = 0;

};

#endif //LABEL_MAP_SOLUTION_HPP