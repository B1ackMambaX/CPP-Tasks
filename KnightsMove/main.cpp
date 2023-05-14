#include <iostream>
#include "funcs.h"
using namespace std;

int main() {
    Node start(7,0,0);
    Node end(6,2,0);
    cout << findShortestDistance(start, end);
    return 0;


}


