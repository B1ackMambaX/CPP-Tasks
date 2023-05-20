#include <string>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

class Game {
	map<string, int*> turns;
	ofstream out;
	int difficulty; bool turn;

	int check_win(string);

	int* rec(string, bool);

	void print_field(string);

	bool is_win_in_one_move(string, bool);

public:
	Game(int dif, bool t) { this->difficulty = dif; this->turn = t; }
	void start();
};