#include <vector>

#include "Rigidbody.h"
#include "Vec2.h"

using namespace std;

#ifndef Intersection_H
#define Intersection_H

struct intersection{
    Rigidbody *c1, *c2;
    Vec2 p;
};

vector<intersection> get_intersections(vector<Rigidbody*>& objects);

#endif