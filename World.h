#include <vector>
#include <stdint.h>


#ifndef World_H
#define World_H

class World {
    
    public:
        void step();
        uint64_t currentTime();

    private:
        std::vector<int> objects;
        uint64_t last_step;

};

#endif