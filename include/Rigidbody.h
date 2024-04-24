#include <vector>

#include "Vec2.h"


#ifndef Rigidbody_H
#define Rigidbody_H

class Rigidbody {
public:
    Rigidbody(std::initializer_list<Vec2> vertices);
    vector<Vec2> getVertices();
    Vec2 getCenter();

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
