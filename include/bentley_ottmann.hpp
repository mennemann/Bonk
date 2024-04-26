#include <vector>

#include "Vec2.h"


#ifndef BentleyOttman_H
#define BentleyOttman_H



template <typename T>
struct intersection{
    T *c1, *c2;
    Vec2 p;
};

template <typename T>
struct segment {
    Vec2 lp, rp;
    T color;

    friend ostream& operator<<(ostream& os, const segment& v) {
        return os << v.p1 << " -- " << v.p2;
    }
};

template <typename T>
vector<intersection<T>> bentley_ottmann(vector<segment<T>> segments);


void test();
#endif