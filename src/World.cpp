#include "World.h"

#include <stdint.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

using namespace std;


World::World() {
    this->last_step = this->currentTime();
}

chrono::high_resolution_clock::time_point World::currentTime() {
    return chrono::high_resolution_clock::now();
}

void World::add(Rigidbody obj) {
    this->objects.push_back(obj);
}


void World::step() {
    auto delta_time_ns = currentTime() - this->last_step;
    this->last_step = currentTime();

    auto delta_time = delta_time_ns.count()/1e9;


    for (Rigidbody& obj : this->objects) {

        obj.velocity += obj.force*(1/obj.mass)*delta_time;

        for (Vec2& v : obj.vertices) {
            v+=obj.velocity*delta_time;
        }
    }

}


void World::render() {
    for (Rigidbody obj : this->objects) {
        glBegin(GL_POLYGON);
        glColor3f(obj.color[0],obj.color[1],obj.color[2]);
        for (Vec2 v : obj.vertices) {
            glVertex2d(v.x/100,v.y/100);
        }
        glEnd();
    }
}