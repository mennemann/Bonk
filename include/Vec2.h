#include <iostream>
#include <math.h>

using namespace std;

class Vec2 {
    public:
        double x;
        double y;

        Vec2(double x, double y) {
            this->x = x;
            this->y = y;
        }

        Vec2 operator+(Vec2 const& other) {
            return Vec2(this->x+other.x, this->y+other.y);
        }

        Vec2 operator-(Vec2 const& other) {
            return Vec2(this->x-other.x, this->y-other.y);
        }

        Vec2 operator*(double const other) {
            return Vec2(this->x*other, this->y*other);
        }

        double operator*(Vec2 const& other) {
            return this->x*other.x + this->y*other.y;
        }

        double length() {
            return sqrt(*this * *this);
        }

        friend ostream& operator<<(ostream& os, const Vec2& v) {
            return os << "(" << v.x << "," << v.y << ")";
        }
};

