#ifndef UNTITLED_INSTANCE_HPP
#define UNTITLED_INSTANCE_HPP

#include <stack>
#include <vector>
#include <representations/PointWithLabel.hpp>

class Instance {
private:
    std::vector<std::shared_ptr<PointWithLabel> > points;

    friend std::ostream &operator<<(std::ostream &ostream, const Instance &instance);

public:
    Instance();

    void reserve(int num);

    void operator+(std::shared_ptr<PointWithLabel> point2D);

    int size() const;

    const std::shared_ptr<PointWithLabel>& getPoint(int idx) const;
};

#endif //UNTITLED_INSTANCE_HPP
