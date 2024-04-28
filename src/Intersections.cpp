#include <vector>

#include "Intersections.h"

#include "Rigidbody.h"
#include "Vec2.h"


struct segment {
    Vec2 p1,p2;
    Rigidbody* color;
};

Vec2* find_intersect(segment* a, segment* b) {
    Vec2 p = a->p1;
    Vec2 r = a->p2 - a->p1;

    Vec2 q = b->p1;
    Vec2 s = b->p2 - b->p1;

    double t = cross(q-p,s)/cross(r,s);
    double u = cross(p-q,r)/cross(s,r);

    if(cross(r,s) != 0) {
        if ((0<t && t<1) && (0<u && u<1)) {
            Vec2 *res = new Vec2();
            *res = p+r*t;
            return res;
        }
    }
    return NULL;
}

vector<intersection> get_intersections(vector<Rigidbody*>& objects) {
    vector<segment> segments;

    for (Rigidbody* obj: objects) {
        auto vertices = obj->getVertices();
        for (unsigned int j = 0; j<vertices.size();j++) {
            int j_ = (j+1)%vertices.size();
            if (vertices[j].x <= vertices[j_].x) {
                segments.push_back({vertices[j], vertices[j_], obj});
            } else segments.push_back({vertices[j_], vertices[j], obj});
        }
    }

    vector<intersection> result;
    
    for (unsigned int i = 0; i<segments.size(); i++) {
        for (unsigned int j = 0; j<segments.size(); j++) {
            if (i==j) continue;
            if(segments[i].color == segments[j].color) continue;

            Vec2 *c = find_intersect(&segments[i], &segments[j]);
            if(c != NULL) result.push_back(intersection{segments[i].color,segments[j].color,*c});
            delete c;
        }
    }

    return result;
}


