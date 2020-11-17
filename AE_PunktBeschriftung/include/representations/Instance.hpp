#pragma once

#include <representations/Point.hpp>
#include <vector>

class Instance {

private:

    std::vector<Point::Ptr> points; // contains all points of the instance TODO should maybe be a map?

    friend std::ostream& operator<<(std::ostream &ostream, const Instance &instance);

public:

    Instance();
    
    Instance(int size);

    void showPoints(); // is only a debug method, can be removed later

    void reserve(int num);

    void add(const Point::Ptr& point);

    int size() const;

    const Point& getPoint(int idx) const;
};

