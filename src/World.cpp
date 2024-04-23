#include "World.h"
#include <stdint.h>

#include <iostream>
#include <chrono>

using namespace std;


void World::step() {
    uint64_t delta_time = currentTime() - this->last_step;



    cout << delta_time;




    this->last_step = currentTime();
};

uint64_t World::currentTime() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
};