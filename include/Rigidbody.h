#include <vector>
#include <limits>
#include "Vec2.h"


#ifndef Rigidbody_H
#define Rigidbody_H

struct max_min {
    double min_x = std::numeric_limits<double>::infinity();
    double max_x = -std::numeric_limits<double>::infinity();
    double min_y = std::numeric_limits<double>::infinity();
    double max_y = -std::numeric_limits<double>::infinity();
};

class Rigidbody {
public:
    Rigidbody(std::initializer_list<Vec2> vertices);
    vector<Vec2> getVertices();
    Vec2 getCenter();
    struct max_min getMaxMin();

    float color[3] = {1, 1, 1};
    void setColor(float r, float g, float b);



    double mass = 1;

    Vec2 position;    
    Vec2 velocity;
    Vec2 force;

    double angle = 0;
    double ang_velocity = 0;
    double torque = 0;

private:
    std::vector<Vec2> vertices;
};


#endif
