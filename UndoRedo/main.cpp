#include <iostream>
#include "funcs.h"
#include <map>
using namespace std;

int main() {
    string command;
    map <string, int> commandList;
    commandList["add"] = 1;
    commandList["del"] = 2;
    commandList["undo"] = 3;
    commandList["redo"] = 4;

    cout << "Commands:" << endl << "undo - go back" << endl << "add - add string" << endl << "del - delete chars" <<
        endl << "redo - go forward" << endl << "exit - close program" << endl;

    while(true) {
        cout << "Enter a command and data: ";
        cin >> command;
        if(command == "exit") {
            break;
        }
        else {
            switch (commandList[command]) {
                case 1:
                    add();
                    break;
                case 2:
                    del();
                    break;
                case 3:
                    undo();
                    break;
                case 4:
                    redo();
                    break;
                default:
                    cout << "There is no such command" << endl;
                    continue;
            }
        }
    }
    return 0;
}
