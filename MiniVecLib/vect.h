#include <string>
#pragma once
struct vec {
    double x;
    double y;
    double z;
    vec(double x, double y, double z);
    vec();
};

vec getSum(vec v1, vec v2);
vec getDiff(vec v1, vec v2);
vec getVecProd(vec v1, vec v2);
double getMixProd(vec v1, vec v2, vec v3);
double getScalarProd(vec v1, vec v2);
vec getNormVec(vec v1);
vec getOrtVec(vec v1, vec v2);
std::string vecToString(vec v1);
double getLength(vec v1);
vec rotate(vec v1, vec v2, double alpha);
