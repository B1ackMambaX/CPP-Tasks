#include <iostream>
#include "vect.h"
#include <cmath>
using  namespace std;

int main() {
    vec v1(1,1,0);
    vec v2(0,0,1);
    cout << vecToString(rotate(v1, v2, 90));
}
