#include <iostream>
#include <math.h>

#include "Vec2.h"

using namespace std;

Vec2::Vec2()
{
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vec2 Vec2::operator+(Vec2 const &other)
{
    return Vec2(this->x + other.x, this->y + other.y);
}

void Vec2::operator+=(Vec2 const &other)
{
    this->x += other.x;
    this->y += other.y;
}

Vec2 Vec2::operator-(Vec2 const &other)
{
    return Vec2(this->x - other.x, this->y - other.y);
}

Vec2 Vec2::operator*(double const other)
{
    return Vec2(this->x * other, this->y * other);
}

void Vec2::operator*=(double const other)
{
    this->x *= other;
    this->y *= other;
}

double Vec2::operator*(Vec2 const &other)
{
    return this->x * other.x + this->y * other.y;
}

bool Vec2::operator==(Vec2 const &other)
{
    return this->x == other.x && this->y == other.y;
}

double Vec2::length()
{
    return sqrt(*this * *this);
}

double cross(Vec2 v, Vec2 w) {
    return v.x*w.y - v.y*w.x;
}

Vec2 Vec2::rotate(double angle, Vec2 ref) {
    double x = cos(angle)*(this->x-ref.x) - sin(angle)*(this->y-ref.y) + ref.x;
    double y = sin(angle)*(this->x-ref.x) + cos(angle)*(this->y-ref.y) + ref.y;
    return Vec2(x,y);
}