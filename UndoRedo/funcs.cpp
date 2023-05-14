#include <iostream>
#include <list>
#include "funcs.h"
//-----------------------Блок с реализацией односвязного списка-------------------------------------------------------
Stack::Node::Node(int op, std::string data, Node* next) {
    this->op = op;
    this->data = data;
    this->next = next;
}

Stack::Stack() {
    this->last = nullptr;
    this->first = nullptr;
    this->size = 0;
}

bool Stack::isEmtpy() {
    return first == nullptr;
}

void Stack::push(std::string data, int op){
    Node* newNode = new Node(op, data, nullptr);
    if(isEmtpy()) {
        last = newNode;
        first = newNode;
    } else {
        last->next = newNode;
        last = newNode;
    }
    size++;
}

void Stack::pop_first() {
    Node* temp = first;
    first = temp->next;
    delete temp;
}

void Stack::pop() {
    if(isEmtpy()) return;
    if(first == last){
        pop_first();
        return;
    }
    Node* newLast = first;
    while(newLast->next != last) {
        newLast = newLast->next;
    }
    newLast->next = nullptr;
    delete last;
    last = newLast;
    size--;
}

Stack::Node Stack::getLast() {
   return *last;
}

Stack::Node Stack::getFirst() {
    return *first;
}

int Stack::getSize() {
    return size;
}

void Stack::print() {
    Node* iterator = first;
    while(iterator){
        std::cout << iterator->data << " ";
        iterator = iterator->next;
    }
    std::cout << std::endl;
}

void Stack::clear() {
    Node* previous = first;
    Node* iterator;
    for(int i = 0; i < size; i++){
        iterator = previous->next;
        delete previous;
        previous = iterator;
    }
    size = 0;
    last = nullptr;
    first = nullptr;
}
//-------------------------------Реализация текстового редактора------------------------------------------------
std::string inputStr;
std::string curStr = "";
Stack undoStack;
Stack redoStack;

void add() {
    if(!redoStack.isEmtpy()) {
        redoStack.clear();
    }
    undoStack.push(curStr, 1);
    getline(std::cin, inputStr);
    inputStr = inputStr.substr(1, inputStr.size() - 1);
    curStr += inputStr;
    std::cout << "Your string is: " << curStr << std::endl;
}

void del(){
    if(curStr.length() == 0) {
        std::cout << "It is nothing to delete" << std::endl;
        return;
    }
    if(!redoStack.isEmtpy()) {
        redoStack.clear();
    }
    undoStack.push(curStr, 2);
    getline(std::cin, inputStr);
    inputStr = inputStr.substr(1, inputStr.size() - 1);
    curStr = curStr.substr(0, curStr.size() - stoi(inputStr));
    std::cout << "Your string is: " << curStr << std::endl;
}

void undo(){
    if(undoStack.isEmtpy()) {
        std::cout << "It's nothing to undo" << std::endl;
        return;
    }
    redoStack.push(curStr, 3);
    curStr = undoStack.getLast().data;
    undoStack.pop();
    std::cout << "Your string is: " << curStr << std::endl;
}

void redo(){
    if(redoStack.isEmtpy()) {
        std::cout << "It's nothing to redo" << std::endl;
        return;
    }
    undoStack.push(curStr, 4);
    curStr = redoStack.getLast().data;
    redoStack.pop();
    std::cout << "Your string is: " << curStr << std::endl;
}


