
#include "bentley_ottmann.hpp"
#include "Vec2.h"

#include <vector>
#include <queue>
#include <set>

using namespace std;

template <typename T>
struct event_point {
    Vec2 p;
    segment<T>* parent;
    segment<T>* intersect;

    bool operator>(const event_point& other) const {
        if (p.x == other.p.x) return p.y > other.p.y;
        return p.x > other.p.x;
    }
};


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

// assuming:
//          No two line segment endpoints or crossings have the same x-coordinate
//          No line segment endpoint lies upon another line segment
//          No three line segments intersect at a single point.
template <typename F>
vector<intersection<F>> bentley_ottmann(vector<segment<F>> segments) {
    priority_queue<event_point<F>, vector<event_point<F>>, greater<event_point<F>>> Q;
    set<segment<F>*> T;

    for (segment<F>& s : segments) {
        Q.push({s.lp, &s, NULL});
        Q.push({s.rp, &s, NULL});
    }

    vector<intersection<F>> intersections;

    while(!Q.empty()) {
        event_point<F> p = Q.top();
        Q.pop();

        cout << "now visiting " << p.p << endl;
    }

    return intersections;
}



void test() { 
    segment<char> a{{1,4},{4,1}, 'a'};
    segment<char> b{{3,1},{6,5}, 'b'};
    segment<char> c{{7,4},{12,2}, 'c'};
    segment<char> d{{5,3},{17,4}, 'd'};
    segment<char> e{{9,5},{11,1}, 'e'};



    bentley_ottmann<char>({d,b,a,c,e});
}