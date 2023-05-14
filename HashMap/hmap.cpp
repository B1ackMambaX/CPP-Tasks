#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "hmap.h"

HashMap::HashMap(int size, int sharp) {
    this->size = size;
    this->sharp = sharp;
    this->arr = new std::list<std::string>[size];
}

HashMap::~HashMap() {
    delete [] arr;
}

int HashMap::hash(std::string word) {
    int hash = 0;
    for(int i = 0; i < word.length(); i++){
        int temp = (int)word[i] * pow(sharp, i);
        hash += temp % size;

    }
    hash %= size;
    arr[hash].push_back(word);
    return hash;
}

void HashMap::print() {
    for(int i = 0; i < size; i++){
        if(arr[i].empty()) continue;
        std::cout << "Hash=" << i << std::endl;
        for(std::string & j : arr[i]){
            std::cout << j << std::endl;
        }
    }
}

void HashMap::getSizeOfHashRows() {
    std::cout << "Sharp:" << sharp << std::endl;
    for(int i = 0; i < size; i++){
        std::cout << "Hash=" << i << "; Number of words: " << arr[i].size() << std::endl;
    }
}

void HashMap::printLog() {
    std::ofstream log;
    log.open("log" + std::to_string(sharp) + ".txt");
    if(!log.is_open()) {
        std::cout << "Error on opening file!" << std::endl;
    }
    log << "Hash:" << sharp << std::endl;
    for(int i = 0; i < size; i++){
        log << i << '\t' << arr[i].size() << std::endl;
    }
    log.close();
}

bool HashMap::contains(std::string word) {
    int hash = 0;
    for(int i = 0; i < word.length(); i++){
        int temp = (int)word[i] * pow(sharp, i);
        hash += temp % size;

    }
    hash %= size;
    for(std::string & j : arr[hash]){
        if(j == word) {
            return true;
        }
    }
    return false;
}



