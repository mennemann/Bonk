#include <vector>

#include "Intersections.h"

#include "Rigidbody.h"
#include "Vec2.h"
#include "bentley_ottmann.hpp"

vector<intersection<Rigidbody*>> get_intersections(vector<Rigidbody*>& objects) {
    vector<segment<Rigidbody*>> segments;

    for (Rigidbody* obj: objects) {
        auto vertices = obj->getVertices();
        for (unsigned int j = 0; j<vertices.size();j++) {
            int j_ = (j+1)%vertices.size();
            if (vertices[j].x <= vertices[j_].x) {
                segments.push_back(segment<Rigidbody*>{vertices[j], vertices[j_], obj});
            } else segments.push_back(segment<Rigidbody*>{vertices[j_], vertices[j], obj});
        }
    }

    //return bentley_ottmann(segments);
    vector<intersection<Rigidbody*>> result;
    return result;
}


