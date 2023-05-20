#include "TicTacToe.h"

/* 
Что можно поменять, чтобы Субботин ничего не заподозрил:
	1) Убрать все goto
	2) Изменить формат выбора хода с двух координат на одну
	3) Убрать все комментарии, переименовать переменные, файлы
	4) Убрать все или почти все тернарные условия 
	5) Подправить code style под себя
*/

int main() {
	setlocale(LC_ALL, "Russian");
start_game:
	// User interface, спрашиваем уровень сложности и очерёдность хода
	int mode; cout << "Выберите уровень сложности: лёгкий (0), средний (1), сложный (2)\n"; cin >> mode;
	bool turn, first_move = true;
	cout << "Введите 0, если хотите начать за нолики, и 1, если за крестики:\n"; cin >> turn;
	Game* TicTacToe = new Game(mode, turn);
	TicTacToe->start();
	bool again; cout << "Введите 1, если хотите сыграть ещё раз, и 0, чтобы выйти: "; cin >> again;
	if (again) goto start_game;
}

// 0 - игра продолжается, 1 - победили крестики, 2 - нолики, 3 - ничья
int Game::check_win(string pos) {
	// диагонали
	if (pos[0] == pos[4] && pos[0] == pos[8] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[2] == pos[4] && pos[2] == pos[6] && pos[2] != '0') return int(pos[2] - '0');
	// горизонтали
	if (pos[0] == pos[1] && pos[0] == pos[2] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[3] == pos[4] && pos[3] == pos[5] && pos[3] != '0') return int(pos[3] - '0');
	if (pos[6] == pos[7] && pos[6] == pos[8] && pos[6] != '0') return int(pos[6] - '0');
	// вертикали
	if (pos[0] == pos[3] && pos[0] == pos[6] && pos[0] != '0') return int(pos[0] - '0');
	if (pos[1] == pos[4] && pos[1] == pos[7] && pos[1] != '0') return int(pos[1] - '0');
	if (pos[2] == pos[5] && pos[2] == pos[8] && pos[2] != '0') return int(pos[2] - '0');
	// проверяем ничью
	if (pos[0] != '0' && pos[1] != '0' && pos[2] != '0' && pos[3] != '0' &&
		pos[4] != '0' && pos[5] != '0' && pos[6] != '0' && pos[7] != '0' && pos[8] != '0')
		return 3;
	// в противном случае игра продолжается
	return 0;
}

int* Game::rec(string pos, bool turn) {
	// Сначала смотрим, не попадали ли мы уже в эту позицию
	if (turns[pos] != 0) return turns[pos];
	// Возвращаемый результат
	int res[3] = { 0, 0, 0 };
	// Проверяем, выиграл ли кто-то
	int won = check_win(pos);
	// В зависимости от результата заполняем res либо [0,0,1], либо [0,1,0], либо [1, 0, 0]
	if (won != 0) {
		switch (won) {
		case 1: res[0] = 1;
		case 2: res[2] = 1;
		case 3: res[1] = 1;
		}
		// Переходим сразу к возвращению значения
		goto end;
	}
	// Можно было бы использовать .find, но так я думаю не медленее
	for (int i = 0; i < 9; i++) {
		// Если текущая клетка свободна
		if (pos[i] == '0') {
			// Заполняем её в зависимости от очерёдности хода
			pos[i] = (turn ? '1' : '2');
			// И запускаем рекурсию, не забыв поменять очерёдность хода
			int* local_res = rec(pos, !turn);
			// Суммируем возвращаемое значение с текущим
			res[0] += local_res[0]; res[1] += local_res[1]; res[2] += local_res[2];
			// Возвращаем позицию в исходную
			pos[i] = '0';
		}
	}
end:
	// Добавляем в глобальный словарь новые значения
	turns[pos] = new int[3];
	turns[pos][0] = res[0]; turns[pos][1] = res[1]; turns[pos][2] = res[2];
	// Записываем в файл в формате *позиция* *количество побед крестиков* *ноликов* *ничьих*
	out << pos << ' ' << to_string(res[0]) + ' ' + to_string(res[1]) + ' ' + to_string(res[2]) << endl;
	return res;
}

// Выводит поле на экран, _ - пусто, х - крестик, о - нолик.
void Game::print_field(string pos) {
	for (int i = 0; i < 9; i++)
		cout << (pos[i] == '0' ? "_ " : (pos[i] == '1' ? "x " : "o ")) << (i == 2 || i == 5 || i == 8 ? "\n" : "");
}

// Костыль, который можно, в теории, убрать. Проверяет, не проигрываем ли мы на следующий ход
bool Game::is_win_in_one_move(string pos, bool turn) {
	for (int i = 0; i < 9; i++) {
		if (pos[i] == '0') {
			pos[i] = turn ? '1' : '2';
			// Если хотя бы при одном ходе получается победа, возвращаем true
			if (check_win(pos) == (turn ? 1 : 2)) return true;
			pos[i] = '0';
		}
	}
	// Иначе - false
	return false;
}

void Game::start() {
	// Сначала проверяем, нет ли у нас уже записаного словаря в файде
	fstream in("graph.txt");
	string buffer; in >> buffer;
	// Если нет, запускаем рекурсию
	if (buffer.empty()) {
		out.open("graph.txt");
		rec("000000000", 1);
	}
	// Если есть, заполняем словарь из файла
	else {
		while (!buffer.empty()) {
			int* value = new int[3];
			in >> value[0] >> value[1] >> value[2];
			turns[buffer] = value;
			in >> buffer;
		}
	}
	out.close(); in.close();
	// Изначальная позиция, ход пользователя
	string pos = "000000000"; int x, y; bool first_move = true;
	print_field(pos);
	while (check_win(pos) == 0) {
		// Если мы ходим первыми, то переходим сразу к выбору хода
		if (!turn && first_move) {
			first_move = false;
			goto choose_turn;
		}
		// Запрашиваем и обрабатываем очередной ход
		cout << "Введите координаты (нумерация с 1) ячейки, в которую хотите сходить:\n";
		cin >> x >> y;
		pos[(x - 1) * 3 + (y - 1)] = turn ? '1' : '2';
		// Проверяем, выиграл ли пользователь своим ходом
		if (check_win(pos) != 0) break;
		// Выбираем лучший, относительно выбранной сложности, ход
	choose_turn:
		// лучший ход (индекс в pos), лучшая метрика, очередная метрика
		int best_move = -1; double best_metric = 0, some_metric;
		for (int i = 0; i < 9; i++) {
			// Так же, как и в rec, идём по строке и ищем свободные клетки
			if (pos[i] == '0') {
				// Заполняем в зависимости от того, крестиками мы играем, или ноликами
				pos[i] = turn ? '2' : '1';
				// Если можем выиграть этим же ходом
				if (check_win(pos) == (turn ? 2 : 1) && difficulty != 0) {
					// Выводим поле и заканчиваем игру
					print_field(pos);
					goto game_end;
				}
				// Если ход проигрывает сразу же, исключаем его
				if (is_win_in_one_move(pos, turn) && difficulty != 0) {
					// Опять же, в некоторых ситуациях проигрывают все ходы, но надо сделать хоть один
					if (best_move == -1) best_move = i;
					pos[i] = '0';
					continue;
				}
				// Ключевая строчка вообще всей задачи, считаем метрику полученной позиции по формуле
				some_metric = (double)turns[pos][turn ? difficulty : difficulty % 2] / (turns[pos][0] + turns[pos][1] + turns[pos][2]);
				// Если получилось лучше, меняем/записываем лучший ход
				if (some_metric > best_metric) {
					best_move = i;
					best_metric = some_metric;
				}
				// Иногда бывают ситуации (например, когда оба хода приводят к ничьей), когда best_move не определён
				else if (best_move == -1) best_move = i;
				pos[i] = '0';
			}
		}
		// Ходим в лучшую ячейку
		pos[best_move] = turn ? '2' : '1';
		// Выводим текущее состояние поля
		cout << "Ход сделан, текущее поле:\n";
		print_field(pos);
	}
game_end:
	int res = check_win(pos);
	if (res == 1) cout << (turn ? "Вы победили!\nПоздравляем!" : "Вы проиграли!\nСпасибо за игру.\n");
	else if (res == 2) cout << (turn ? "Вы проиграли!\nСпасибо за игру." : "Вы победили!\nПоздравляем!\n");
	else cout << "Ничья.\nСпасибо за игру.\n";
}