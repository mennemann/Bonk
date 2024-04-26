
#include "bentley_ottmann.hpp"
#include "Vec2.h"

#include <vector>

using namespace std;


// solves ax + by = c
//        dx + ey = f
inline double* solve_eq(double a, double b, double c, double d, double e, double f) {
    double det = a*e - d*b;
    if (det == 0) return NULL;

    double *solutions = new double[2];

    solutions[0] = (c*e - f*b)/det;
    solutions[1] = (a*f - d*c)/det;

    return solutions;
}

template <typename T>
Vec2* find_intersect(segment<T>* a, segment<T>* b) {
    if (a == NULL || b == NULL) return NULL;
    Vec2 da = a->p2 - a->p1;
    Vec2 db = b->p2 - b->p1;

    
    // solving  da * r + a1 = db * t + b1   <=>   da * r - db * t = b1 - a1
    double* solutions = solve_eq(       
        da.x, -db.x, b->p1.x - a->p1.x,
        da.y, -db.y, b->p1.y - a->p1.y
        );

    if (solutions == NULL) return NULL;
    if (!(0 < solutions[0] && solutions[0] < 1)) return NULL;

    Vec2 s1 = da*solutions[0] +a->p1;
    Vec2 s2 = db*solutions[1] +b->p1;
    
    delete [] solutions;

    Vec2 *res = new Vec2();
    *res = s1;

    return res;
}


template <typename T>
vector<intersection<T>> bentley_ottmann(vector<segment<T>>) {
    
}



void test() {

}