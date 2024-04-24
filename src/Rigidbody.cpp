#include "Rigidbody.h"
#include "Vec2.h"

Rigidbody::Rigidbody(std::initializer_list<Vec2> vertices) {
    this->vertices = vertices;
}

Vec2 Rigidbody::getCenter() {
    Vec2 sum;

    for (Vec2 v : this->vertices) {
        sum += v;
    }

    sum *= 1/this->vertices.size();

    return sum;
}

void Rigidbody::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}