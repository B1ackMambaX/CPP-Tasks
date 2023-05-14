#include "funcs.h"
#include "list"
#include "queue"

bool isField(int x, int y) {
    return (x >= 0 && x < 8) && (y >= 0 && y < 8);
}
bool isVisited(Node curNode, std::list<Node> visited) {
    for(Node j : visited) {
        if(j.x == curNode.x && j.y == curNode.y && j.dist == curNode.dist) {
            return true;
        }
    }
    return false;
}

int findShortestDistance(Node start, Node end) {
    int moves[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    std::list <Node> visited;
    std::queue <Node> queue;
    queue.push(start);

    while(!queue.empty()) {
        Node curr = queue.front();
        queue.pop();

        if(curr.x == end.x && curr.y == end.y) {
            return curr.dist;
        }
        if(!isVisited(curr, visited)) {
            visited.push_back(curr);
            for(int i = 0; i < 8; i++) {
                int x = curr.x + moves[i][0];
                int y = curr.y + moves[i][1];
                if(isField(x, y)) {
                    queue.push(Node(x, y, curr.dist + 1));
                }
            }
        }
    }
    return -1;
}

Node::Node(int x, int y, int dist) {
    this->x = x;
    this->y = y;
    this->dist = dist;
}

