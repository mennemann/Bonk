#include "Rigidbody.h"
#include "Vec2.h"
#include <deque>
#include <vector>

Rigidbody::Rigidbody(std::initializer_list<Vec2> vertices) {
    deque<Vec2> v = vertices;
    this->position = v.front();

    while (!v.empty())
    {
        struct max_min d;
        if (v.front().x < d.min_x) d.min_x = v.front().x;
        if (v.front().x > d.max_x) d.max_x = v.front().x;
        if (v.front().x < d.min_y) d.min_y = v.front().y;
        if (v.front().x > d.max_y) d.max_y = v.front().y;
        this->max_min = d;

        this->vertices.push_back(v.front()-this->position);
        v.pop_front();
    }
    
}


vector<Vec2> Rigidbody::getVertices() {
    Vec2 center = this->getCenter();
    vector<Vec2> pos;

    for (Vec2 v : this->vertices) {
        pos.push_back(
            (this->position+v).rotate(this->angle, center)
        );
    }

    return pos;
}


Vec2 Rigidbody::getCenter() {
    Vec2 center;
    for (Vec2 v : this->vertices) {
        center += v;
    }
    return this->position+center*((double)1/this->vertices.size());
}

struct max_min Rigidbody::getMaxMin() {
    return this->max_min;
}

void Rigidbody::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}