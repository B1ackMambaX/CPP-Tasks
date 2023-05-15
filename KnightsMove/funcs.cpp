#include "funcs.h"
#include "list"
#include "queue"
#include "iostream"

bool isField(int x, int y) {
    return (x >= 0 && x < 8) && (y >= 0 && y < 8);
}
bool isVisited(Node curNode, std::list<Node> visited) {
    for(Node j : visited) {
        if(j.x == curNode.x && j.y == curNode.y) {
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
        Node * ptr = &queue.front();
        queue.pop();
        if(curr.x == end.x && curr.y == end.y) {
            Node* last = &curr;
            Node* iterator;
            for(int i = 0; i < curr.dist + 1; i++) {
                iterator = last->ptr;
                std::cout << char(last->x + 97)<< '\t' << char(last->y + 49) << std::endl;
                last = iterator;
            }
            return curr.dist;
        }

        if(!isVisited(curr, visited)) {
            visited.push_back(curr);
            for(int i = 0; i < 8; i++) {
                int x = curr.x + moves[i][0];
                int y = curr.y + moves[i][1];
                if(isField(x, y)) {
                    queue.push(Node(x, y, curr.dist + 1, ptr));
                }
            }
        }

    }
    return -1;
}

Node::Node(int x, int y, int dist, Node* ptr) {
    this->x = x;
    this->y = y;
    this->dist = dist;
    this->ptr = ptr;
}

Node::Node(char x, char y, int dist, Node* ptr) {
    this->x = (int) tolower(x) - 97;
    this->y = (int) tolower(y) - 49;
    this->dist = dist;
}

