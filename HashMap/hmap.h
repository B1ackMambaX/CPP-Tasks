#pragma once
#include <list>

class HashMap{
private:
    int size;
    int sharp;
    std::list<std::string>* arr;
public:
    HashMap(int size, int sharp);
    ~HashMap();
    int hash(std::string word);
    bool contains(std::string word);
    void print();
    void getSizeOfHashRows();
    void printLog();
};