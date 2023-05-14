#include "hmap.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    HashMap first(17,7);
    HashMap second(101,2);
    HashMap third(31, 11);
    srand(time(NULL));
    char alph[27] = "abcdefghijklmnopqrstuvwxyz";
    for(int j = 0; j < 10000; j++) {
        char word[5] = {0};
        for (int i = 0; i < 4; i++) {
            word[i] = alph[rand() % 26];
        }
        if (first.contains(string(word))) {
            j--;
        } else {
            first.hash(string(word));
            second.hash(string(word));
            third.hash(string(word));
        }
    }
    first.printLog();
    second.printLog();
    third.printLog();
    return 0;
}

