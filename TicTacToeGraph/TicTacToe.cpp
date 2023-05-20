#include "TicTacToe.h"

/* 
��� ����� ��������, ����� �������� ������ �� ����������:
	1) ������ ��� goto
	2) �������� ������ ������ ���� � ���� ��������� �� ����
	3) ������ ��� �����������, ������������� ����������, �����
	4) ������ ��� ��� ����� ��� ��������� ������� 
	5) ���������� code style ��� ����
*/

int main() {
	setlocale(LC_ALL, "Russian");
start_game:
	// User interface, ���������� ������� ��������� � ���������� ����
	int mode; cout << "�������� ������� ���������: ����� (0), ������� (1), ������� (2)\n"; cin >> mode;
	bool turn, first_move = true;
	cout << "������� 0, ���� ������ ������ �� ������, � 1, ���� �� ��������:\n"; cin >> turn;
	Game* TicTacToe = new Game(mode, turn);
	TicTacToe->start();
	bool again; cout << "������� 1, ���� ������ ������� ��� ���, � 0, ����� �����: "; cin >> again;
	if (again) goto start_game;
}

// 0 - ���� ������������, 1 - �������� ��������, 2 - ������, 3 - �����
int Game::check_win(string pos) {
	// ���������
	if (pos[0] == pos[4] && pos[0] == pos[8] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[2] == pos[4] && pos[2] == pos[6] && pos[2] != '0') return int(pos[2] - '0');
	// �����������
	if (pos[0] == pos[1] && pos[0] == pos[2] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[3] == pos[4] && pos[3] == pos[5] && pos[3] != '0') return int(pos[3] - '0');
	if (pos[6] == pos[7] && pos[6] == pos[8] && pos[6] != '0') return int(pos[6] - '0');
	// ���������
	if (pos[0] == pos[3] && pos[0] == pos[6] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[1] == pos[4] && pos[1] == pos[7] && pos[1] != '0') return int(pos[1] - '0');
	if (pos[2] == pos[5] && pos[2] == pos[8] && pos[2] != '0') return int(pos[2] - '0');
	// ��������� �����
	if (pos[0] != '0' && pos[1] != '0' && pos[2] != '0' && pos[3] != '0' &&
		pos[4] != '0' && pos[5] != '0' && pos[6] != '0' && pos[7] != '0' && pos[8] != '0')
		return 3;
	// � ��������� ������ ���� ������������
	return 0;
}

int* Game::rec(string pos, bool turn) {
	// ������� �������, �� �������� �� �� ��� � ��� �������
	if (turns[pos] != 0) return turns[pos];
	// ������������ ���������
	int res[3] = { 0, 0, 0 };
	// ���������, ������� �� ���-��
	int won = check_win(pos);
	// � ����������� �� ���������� ��������� res ���� [0,0,1], ���� [0,1,0], ���� [1, 0, 0]
	if (won != 0) {
		switch (won) {
		case 1: res[0] = 1;
		case 2: res[2] = 1;
		case 3: res[1] = 1;
		}
		// ��������� ����� � ����������� ��������
		goto end;
	}
	// ����� ���� �� ������������ .find, �� ��� � ����� �� ��������
	for (int i = 0; i < 9; i++) {
		// ���� ������� ������ ��������
		if (pos[i] == '0') {
			// ��������� � � ����������� �� ���������� ����
			pos[i] = (turn ? '1' : '2');
			// � ��������� ��������, �� ����� �������� ���������� ����
			int* local_res = rec(pos, !turn);
			// ��������� ������������ �������� � �������
			res[0] += local_res[0]; res[1] += local_res[1]; res[2] += local_res[2];
			// ���������� ������� � ��������
			pos[i] = '0';
		}
	}
end:
	// ��������� � ���������� ������� ����� ��������
	turns[pos] = new int[3];
	turns[pos][0] = res[0]; turns[pos][1] = res[1]; turns[pos][2] = res[2];
	// ���������� � ���� � ������� *�������* *���������� ����� ���������* *�������* *������*
	out << pos << ' ' << to_string(res[0]) + ' ' + to_string(res[1]) + ' ' + to_string(res[2]) << endl;
	return res;
}

// ������� ���� �� �����, _ - �����, � - �������, � - �����.
void Game::print_field(string pos) {
	for (int i = 0; i < 9; i++)
		cout << (pos[i] == '0' ? "_ " : (pos[i] == '1' ? "x " : "o ")) << (i == 2 || i == 5 || i == 8 ? "\n" : "");
}

// �������, ������� �����, � ������, ������. ���������, �� ����������� �� �� �� ��������� ���
bool Game::is_win_in_one_move(string pos, bool turn) {
	for (int i = 0; i < 9; i++) {
		if (pos[i] == '0') {
			pos[i] = turn ? '1' : '2';
			// ���� ���� �� ��� ����� ���� ���������� ������, ���������� true
			if (check_win(pos) == (turn ? 1 : 2)) return true;
			pos[i] = '0';
		}
	}
	// ����� - false
	return false;
}

void Game::start() {
	// ������� ���������, ��� �� � ��� ��� ���������� ������� � �����
	fstream in("graph.txt");
	string buffer; in >> buffer;
	// ���� ���, ��������� ��������
	if (buffer.empty()) {
		out.open("graph.txt");
		rec("000000000", 1);
	}
	// ���� ����, ��������� ������� �� �����
	else {
		while (!buffer.empty()) {
			int* value = new int[3];
			in >> value[0] >> value[1] >> value[2];
			turns[buffer] = value;
			in >> buffer;
		}
	}
	out.close(); in.close();
	// ����������� �������, ��� ������������
	string pos = "000000000"; int x, y; bool first_move = true;
	print_field(pos);
	while (check_win(pos) == 0) {
		// ���� �� ����� �������, �� ��������� ����� � ������ ����
		if (!turn && first_move) {
			first_move = false;
			goto choose_turn;
		}
		// ����������� � ������������ ��������� ���
		cout << "������� ���������� (��������� � 1) ������, � ������� ������ �������:\n";
		cin >> x >> y;
		pos[(x - 1) * 3 + (y - 1)] = turn ? '1' : '2';
		// ���������, ������� �� ������������ ����� �����
		if (check_win(pos) != 0) break;
		// �������� ������, ������������ ��������� ���������, ���
	choose_turn:
		// ������ ��� (������ � pos), ������ �������, ��������� �������
		int best_move = -1; double best_metric = 0, some_metric;
		for (int i = 0; i < 9; i++) {
			// ��� ��, ��� � � rec, ��� �� ������ � ���� ��������� ������
			if (pos[i] == '0') {
				// ��������� � ����������� �� ����, ���������� �� ������, ��� ��������
				pos[i] = turn ? '2' : '1';
				// ���� ����� �������� ���� �� �����
				if (check_win(pos) == (turn ? 2 : 1) && difficulty != 0) {
					// ������� ���� � ����������� ����
					print_field(pos);
					goto game_end;
				}
				// ���� ��� ����������� ����� ��, ��������� ���
				if (is_win_in_one_move(pos, turn) && difficulty != 0) {
					// ����� ��, � ��������� ��������� ����������� ��� ����, �� ���� ������� ���� ����
					if (best_move == -1) best_move = i;
					pos[i] = '0';
					continue;
				}
				// �������� ������� ������ ���� ������, ������� ������� ���������� ������� �� �������
				some_metric = (double)turns[pos][turn ? difficulty : difficulty % 2] / (turns[pos][0] + turns[pos][1] + turns[pos][2]);
				// ���� ���������� �����, ������/���������� ������ ���
				if (some_metric > best_metric) {
					best_move = i;
					best_metric = some_metric;
				}
				// ������ ������ �������� (��������, ����� ��� ���� �������� � ������), ����� best_move �� ��������
				else if (best_move == -1) best_move = i;
				pos[i] = '0';
			}
		}
		// ����� � ������ ������
		pos[best_move] = turn ? '2' : '1';
		// ������� ������� ��������� ����
		cout << "��� ������, ������� ����:\n";
		print_field(pos);
	}
game_end:
	int res = check_win(pos);
	if (res == 1) cout << (turn ? "�� ��������!\n�����������!" : "�� ���������!\n������� �� ����.\n");
	else if (res == 2) cout << (turn ? "�� ���������!\n������� �� ����." : "�� ��������!\n�����������!\n");
	else cout << "�����.\n������� �� ����.\n";
}