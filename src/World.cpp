#include "World.h"

#include <stdint.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

using namespace std;


World::World() {
    this->last_step = this->currentTime();
}

uint64_t World::currentTime() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
};

void World::add(Rigidbody obj) {
    this->objects.push_back(obj);
}


void World::step() {
    uint64_t delta_time = currentTime() - this->last_step;

    this->last_step = currentTime();
};


void World::render() {
    for (Rigidbody obj : this->objects) {
        glBegin(GL_POLYGON);
        glColor3f(obj.color[0],obj.color[1],obj.color[2]);
        for (Vec2 v : obj.getVertices()) {
            glVertex2d(v.x/100,v.y/100);
        }
        glEnd();
    }
}