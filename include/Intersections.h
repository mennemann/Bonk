#include <vector>

#include "bentley_ottmann.hpp"

#include "Rigidbody.h"
#include "Vec2.h"

using namespace std;

#ifndef Intersection_H
#define Intersection_H

vector<intersection<Rigidbody*>> get_intersections(vector<Rigidbody*>& objects);

#endif