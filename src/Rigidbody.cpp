#include "Rigidbody.h"
#include "Vec2.h"
#include <deque>
#include <vector>

Rigidbody::Rigidbody(std::initializer_list<Vec2> vertices) {
    deque<Vec2> v = vertices;
    this->position = v.front();

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

struct max_min Rigidbody::getMaxMin() {
    struct max_min d;
    for (Vec2 v : this->getVertices()) {
        if (v.x < d.min_x) d.min_x = v.x;
        if (v.x > d.max_x) d.max_x = v.x;
        if (v.y < d.min_y) d.min_y = v.y;
        if (v.y > d.max_y) d.max_y = v.y;
    }
    return d;
}

void Rigidbody::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}



void Rigidbody::applyImpulse(Vec2 J, Vec2 anchor) {
    this->velocity += J*(1/this->mass);
    this->ang_velocity += cross(anchor-this->getCenter(),J)/this->inertia;
}