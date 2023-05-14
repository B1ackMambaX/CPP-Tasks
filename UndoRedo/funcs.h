#pragma once
class Stack {
private:
    struct Node {
        int op;
        std::string data;
        Node* next = nullptr;
        Node(int op, std::string data, Node* next);
        //~Node();
    };
    int size;
    Node* last;
    Node* first;
public:
    Stack();
    bool isEmtpy();
    void push(std::string data, int op);
    void pop();
    void pop_first();
    Node getLast();
    Node getFirst();
    int getSize();
    void print();
    void clear();
};



void add();
void del();
void undo();
void redo();

