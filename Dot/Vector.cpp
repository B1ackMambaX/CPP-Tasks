#include "Vector.h"
Vector::Vector(double a, double b, double c){
    this->x = a;
    this->y = b;
    this->z = c;
}

Vector::Vector(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector Vector::operator+(Vector v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(double a) const {
    return Vector(a*x, a*y, a*z);
}

Vector Vector::operator/(double a) const {
    return Vector(x/a, y/a, z/a);
}

bool Vector::operator==(Vector a) const {
    return (x == a.x) && (y == a.y) && (z == a.z);
}

double Vector::operator*(Vector a) const{
    return x*a.x + y*a.y + z*a.z;
}

Plane::Plane(double a, double b, double c, double d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Plane::Plane() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
}

Point::Point(double a, double b, double c) {
    this->x = a;
    this->y = b;
    this->z = c;
}

Point::Point(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Line::Line(Point p, Vector v) {
    this->p = p;
    this->v = v;
}

Line::Line() {
    this->p = Point();
    this->v = Vector();
}
