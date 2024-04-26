#include <vector>
#include <stdint.h>
#include <chrono>
#include "Rigidbody.h"

#ifndef World_H
#define World_H

class World {
    
    public:
        World();
        void step();
        void render();
        void add(Rigidbody obj);

    private:
        std::vector<Rigidbody> objects;
        
        std::chrono::high_resolution_clock::time_point last_step;
        std::chrono::high_resolution_clock::time_point currentTime();

};

#endif