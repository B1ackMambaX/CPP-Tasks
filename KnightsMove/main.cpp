#include <iostream>
#include "funcs.h"
using namespace std;

int main() {
    string startPos;
    string endPos;
    cout << "Enter starting cell: ";
    cin >> startPos;

    cout << "Enter finishing cell: ";
    cin >> endPos;

    /*int x1 = (int)tolower(startPos[0]) - 97;
    int y1 = (int)startPos[1] - 49;
    int x2 = (int)tolower(endPos[0]) - 97;
    int y2 = (int)endPos[1] - 49;

    Node start(x1, y1, 0);
    Node end(x2, y2, 0);*/
    Node start(startPos[0], startPos[1], 0, nullptr);
    Node end(endPos[0], endPos[1], 0, nullptr);
    int dist = findShortestDistance(start, end);
    cout << "Shortest distance is: " <<  dist;
    return 0;


}


