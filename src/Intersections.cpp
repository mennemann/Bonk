#include <vector>
#include <algorithm>
#include <queue>

#include "Intersections.h"

#include "Rigidbody.h"
#include "Vec2.h"

using namespace std;

bool intersection::operator==(const intersection& other) {
    return (o1==other.o1 && o2==other.o2 && p == other.p);
}

struct segment {
    Vec2 p1, p2;
    Rigidbody* color;

    double f(double x);

    friend ostream& operator<<(ostream& os, const segment& v) {
        return os << v.p1 << " -- " << v.p2;
    }
};

double segment::f(double x) {
    if (x < p1.x) return p1.y;
    if (p2.x < x) return p2.y;

    double m = (p2.y-p1.y)/(p2.x-p1.x);
    double b = p1.y - m * p1.x; // m * p1.x + b = p1.y  <=> b = p1.y - m * p1.x

    return m*x+b;
}

struct event_point {
    Vec2 p;
    segment* parent;
    segment* intersect;

    bool operator>(const event_point& other) const {
        if (p.x == other.p.x) return p.y > other.p.y;
        return p.x > other.p.x;
    }
};



// finde das erste i, so dass T[i].f(s->p1.x) > s->p1.y
void insert(segment *s, vector<segment*>& T) {
    unsigned int i;
    for (i = 0; i<T.size(); i++) {
        if (T[i]->f(s->p1.x) > s->p1.y) break;
    }
    T.insert(T.begin()+i,s);
}

void remove(segment *s, vector<segment*>& T) {
    T.erase(remove(T.begin(), T.end(), s), T.end());
}

void swap(segment *s, segment* r, vector<segment*>& T) { // assume s and r in T
    auto i_s = find(T.begin(), T.end(), s);
    auto i_r = find(T.begin(), T.end(), r);
    iter_swap(i_s, i_r);
}

unsigned int index(segment *s, vector<segment*>& T) {
    unsigned int i = find(T.begin(), T.end(), s) - T.begin(); // assume s is def. in T
    return i;
}

segment* predecessor(segment* s, vector<segment*>& T) {
    unsigned int i = index(s,T);
    if (i > 0) return T[i-1];
    return NULL;
}

segment* successor(segment* s, vector<segment*>& T) {
    unsigned int i = index(s,T);
    if (i+1 < T.size()) return T[i+1];
    return NULL;
}

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

Vec2* find_intersect(segment* a, segment* b) {
    if (a == NULL || b == NULL) return NULL;
    Vec2 da = a->p2 - a->p1;
    Vec2 db = b->p2 - b->p1;

    // solving  da * r + a1 = db * t + b1
    //          da * r - db * t = b1 - a1

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

    cout << *a <<" , " << *b << endl;
    cout << s1 << " " << s2 << endl; 

    return res;
}

vector<intersection> bentley_ottman(vector<segment> segments) {
    priority_queue<event_point, vector<event_point>, greater<event_point>> Q;
    vector<segment*> T;

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

        if(p.parent != NULL && p.intersect != NULL) { // p is intersect
            if(p.parent->color == p.intersect->color) continue;
            intersections.push_back(intersection{p.parent->color, p.intersect->color, p.p});
            swap(p.parent, p.intersect);

            segment *lower, *upper;
            if (index(p.parent, T) < index(p.intersect,T)) {
                lower = p.parent;
                upper = p.intersect;
            } else {
                lower = p.intersect;
                upper = p.parent;
            }
            u = predecessor(lower,T);
            t = successor(upper,T);
            Vec2* c1 = find_intersect(lower, u);
            Vec2* c2 = find_intersect(upper, t);
            if (c1 != NULL) Q.push({*c1, lower, u});
            if (c2 != NULL) Q.push({*c2, upper, t});
            delete c1;
            delete c2;

        } else if (p.p == s->p1) { // p is left endpoint
            insert(s,T);            
            
            u = predecessor(s, T);
            t = successor(s, T);
            Vec2* c1 = find_intersect(u, s);
            Vec2* c2 = find_intersect(s, t);
            if (c1 != NULL) Q.push({*c1, u, s});
            if (c2 != NULL) Q.push({*c2, s, t});
            delete c1;
            delete c2;
        } else if (p.p == s->p2) { // p is right endpoint
            u = predecessor(s, T);
            t = successor(s, T);
            Vec2* c1 = find_intersect(u, t);
            if (c1 != NULL) Q.push({*c1, u, t});
            delete c1;
            remove(s,T);
        }
    }
    
    return intersections;
}


vector<intersection> get_intersections(vector<Rigidbody*>& objects) {
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


