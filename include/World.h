#include <vector>
#include <stdint.h>

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
        uint64_t last_step;
        uint64_t currentTime();

};

#endif