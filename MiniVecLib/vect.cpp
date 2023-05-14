//Структура трехмерного вектора
//длина, скалярное, смешанное, векторное произведение, нормировка, построение ортогонального вектора к двум данным
#include "vect.h"
#include <cmath>
#include <numeric>
using namespace std;

vec::vec(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
vec::vec() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
vec getSum(vec v1, vec v2){
    vec sum;
    sum.x = v1.x + v2.x;
    sum.y = v1.y + v2.y;
    sum.z = v1.z + v2.z;
    return sum;
}
double getLength(vec v1){
    double len = sqrt(pow(v1.x, 2)+pow(v1.y, 2)+pow(v1.z, 2));
    return  len;
}
vec getDiff(vec v1, vec v2){
    vec diff;
    diff.x = v1.x - v2.x;
    diff.y = v1.y - v2.y;
    diff.z = v1.z - v2.z;
    return diff;
}
vec getScalarMult(vec v1, double scalar){
    vec res;
    res.x = v1.x * scalar;
    res.y = v1.y * scalar;
    res.z = v1.z * scalar;
    return  res;
}
vec getVecProd(vec v1, vec v2){
    vec res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return res;
}
double getMixProd(vec v1, vec v2, vec v3){
    vec v1v2 = getVecProd(v1, v2);
    double res = getScalarProd(v1v2, v3);
    return  res;
}

double getScalarProd(vec v1, vec v2){
    double res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return res;
}
vec getNormVec(vec v1){
    vec norm;
    double length = getLength(v1);
    if(abs(length) >= numeric_limits<double>::epsilon()){
        norm.x = v1.x / length;
        norm.y = v1.y / length;
        norm.z = v1.z / length;
    }
    return norm;
}

vec getOrtVec(vec v1, vec v2){
    vec res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    res = getNormVec(res);
    return res;
}

string vecToString(vec v1){
    string res = to_string(v1.x) + " " + to_string(v1.y) + " " + to_string(v1.z);
    return res;
}

vec rotate(vec v1, vec v2, double alpha){
    vec v3 = getNormVec(getOrtVec(v1, v2));
    alpha = alpha * M_PI / 180;
    double matrix[3][3];
    matrix[0][0] = cos(alpha) + (1 - cos(alpha)) * v3.x * v3.x;
    matrix[0][1] = (1 - cos(alpha)) * v3.x * v3.y - sin(alpha) * v3.z;
    matrix[0][2] = (1 - cos(alpha)) * v3.x * v3.z + sin(alpha) * v3.y;
    matrix[1][0] = (1 - cos(alpha)) * v3.y * v3.x + sin(alpha) * v3.z;
    matrix[1][1] = cos(alpha) + (1 - cos(alpha)) * v3.y * v3.y;
    matrix[1][2] = (1 - cos(alpha)) * v3.y *v3.z - sin(alpha) * v3.x;
    matrix[2][0] = (1 - cos(alpha)) * v3.z * v3.x - sin(alpha) * v3.y;
    matrix[2][1] = (1 - cos(alpha)) * v3.z * v3.y + sin(alpha) * v3.x;
    matrix[2][2] = cos(alpha) + (1 - cos(alpha)) * v3.z * v3.z;
    vec res;
    res.x = matrix[0][0] * v1.x + matrix[0][1] * v1.y + matrix[0][2] * v1.z;
    res.y = matrix[1][0] * v1.x +matrix[1][1] * v1.y + matrix[1][2] * v1.z;
    res.z = matrix[2][0] * v1.x +matrix[2][1] * v1.y + matrix[2][2] * v1.z;
    return res;
}