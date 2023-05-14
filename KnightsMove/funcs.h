#pragma once

struct Node {
    int x;
    int y;
    int dist = 0;
    Node(int x, int y, int dist);
};

int findShortestDistance(Node start, Node end);

