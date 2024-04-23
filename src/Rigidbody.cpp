#include "Rigidbody.h"
#include "Vec2.h"

Rigidbody::Rigidbody(std::initializer_list<Vec2> vertices) {
    this->vertices = vertices;
}

std::vector<Vec2> Rigidbody::getVertices() {
    return this->vertices;
}