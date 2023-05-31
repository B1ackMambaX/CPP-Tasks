#include "iostream"
#include "cmath"
#include "string"
#include "limits"

using namespace std;

#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    double x, y, z;

    Vector(double, double, double);
    Vector();
    Vector operator +(Vector) const;
    Vector operator -(Vector) const;
    Vector operator * (double) const;
    Vector operator / (double) const;
    bool operator == (Vector) const;
    double operator * (Vector) const;
};

struct Plane{
    double a, b, c ,d;
    Plane(double a, double b, double c, double d);
    Plane();
};

struct Point{
    double x, y, z;
    Point(double a, double b, double c);
    Point();
};

struct Line{
    Point p;
    Vector v;
    Line(Point, Vector);
    Line();
};

#endif //VECTOR_H
