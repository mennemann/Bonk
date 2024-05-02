#include <vector>

#include "Rigidbody.h"
#include "Vec2.h"

using namespace std;

#ifndef Intersection_H
#define Intersection_H

struct intersection{
    Rigidbody *c1, *c2;
    Vec2 p;

    bool operator==(intersection const& other) {
        return c1 == other.c1 && c2 == other.c2 && p == other.p;
    }
};

vector<intersection> get_intersections(vector<Rigidbody*>& objects);
Vec2* estimate_collosion_point(Rigidbody& a, Rigidbody& b);
#endif