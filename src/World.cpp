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


void World::step() {
    uint64_t delta_time = currentTime() - this->last_step;

    this->last_step = currentTime();
};


void World::render() {
        glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.0f, 0.6f);
        glEnd();
}