#pragma once

struct Node {
    int x;
    int y;
    int dist = 0;
    Node* ptr;
    Node(int x, int y, int dist, Node* ptr);
    Node(char x, char y, int dist, Node* ptr);
};

int findShortestDistance(Node start, Node end);

