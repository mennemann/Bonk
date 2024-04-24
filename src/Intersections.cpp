#include <vector>
#include <algorithm>
#include <queue>
#include <set>

#include "Intersections.h"

#include "Rigidbody.h"
#include "Vec2.h"

using namespace std;

struct segment {
    Vec2 p1, p2;
    Rigidbody* color;
};

inline bool operator<(const segment& a, const segment& b) {
    // it looks easy but no...
    return false;
}

struct event_point {
    Vec2 p;
    segment* parent;
    segment* intersect;

    bool operator>(const event_point& other) const {
        return p.x > other.p.x;
    }
};



segment* successor(segment* s, set<segment>* T) {
    return NULL;
}

segment* predecessor(segment* s, set<segment>* T) {
    return NULL;
}

Vec2* find_intersect(segment* a, segment* b) {
    return NULL;
}

vector<intersection> bentley_ottman(vector<segment> segments) {

    priority_queue<event_point, vector<event_point>, greater<event_point>> Q;
    set<segment> T;

    for (auto& s : segments) {
        Q.push(event_point{s.p1, &s, NULL});
        Q.push(event_point{s.p2, &s, NULL});
    }


    vector<intersection> intersections;

    segment *u, *t;

    while (!Q.empty()) {
        event_point p = Q.top();
        Q.pop();

        segment* s = p.parent;
        if(p.intersect != NULL) { // p is intersect
            //intersections.push_back(intersection{p.parent->color, p.intersect->color, });
        } else if (p.p == s->p1) { // p is left endpoint
            T.insert(*s);            
            
            u = predecessor(s, &T);
            t = successor(s, &T);
            Vec2* c1 = find_intersect(u, s);
            Vec2* c2 = find_intersect(s, t);
            if (c1 != NULL) Q.push({*c1, u, s});
            if (c2 != NULL) Q.push({*c2, s, t});
            delete c1;
            delete c2;
        } else if (p.p == s->p2) { // p is right endpoint
            u = predecessor(s, &T);
            t = successor(s, &T);
            Vec2* c1 = find_intersect(u, s);
            Vec2* c2 = find_intersect(s, t);
            if (c1 != NULL) Q.push({*c1, u, s});
            if (c2 != NULL) Q.push({*c2, s, t});
            delete c1;
            delete c2;

            T.erase(*s);
        } else { 
            cout << "wtf" << endl;
        }
    }

    
    return intersections;
}


vector<intersection> get_intersections(vector<Rigidbody*> objects) {
    vector<segment> segments;

    for (Rigidbody* obj: objects) {
        auto vertices = obj->getVertices();
        for (unsigned int j = 0; j<vertices.size();j++) {
            int j_ = (j+1)%vertices.size();
            if (vertices[j].x <= vertices[j_].x) {
                segments.push_back(segment{vertices[j], vertices[j_], obj});
            } else segments.push_back(segment{vertices[j_], vertices[j], obj});
        }
    }

    return bentley_ottman(segments);
}


