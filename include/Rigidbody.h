#include <vector>

#include "Vec2.h"


#ifndef Rigidbody_H
#define Rigidbody_H

class Rigidbody {
public:
    Rigidbody(std::initializer_list<Vec2> vertices);
    std::vector<Vec2> vertices;

    float color[3] = {1, 1, 1};

    void setColor(float r, float g, float b);

    Vec2 velocity;
    Vec2 force;
    double mass = 1;
};


#endif
