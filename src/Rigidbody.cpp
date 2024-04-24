#include "Rigidbody.h"
#include "Vec2.h"
#include <deque>
#include <vector>

Rigidbody::Rigidbody(std::initializer_list<Vec2> vertices) {
    deque<Vec2> v = vertices;
    this->position = v.front();
    v.pop_front();

    this->vertices.push_back({0,0});
    while (!v.empty())
    {
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


void Rigidbody::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}