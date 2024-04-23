#include <iostream>
#include <math.h>

#include "Vec2.h"

using namespace std;

Vec2::Vec2(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(Vec2 const &other)
{
    return Vec2(this->x + other.x, this->y + other.y);
}

Vec2 Vec2::operator-(Vec2 const &other)
{
    return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator*(double const other)
{
    return Vec2(this->x * other, this->y * other);
}

double Vec2::operator*(Vec2 const &other)
{
    return this->x * other.x + this->y * other.y;
}

double Vec2::length()
{
    return sqrt(*this * *this);
}