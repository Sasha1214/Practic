#include <iostream>
#include "XO.h"
#include<ctime>

using namespace std;

Game initGame(char userChar) {
	srand(time(NULL));

	Game i;
	for (int d = 0; d < 3; d++)
		for (int r = 0; r < 3; r++)
			i.board[d][r] = ' ';

	if (rand() % 2) {
		i.isUserTurn = true; //ход пользователя
	}
	else {
		i.isUserTurn = false; //ход бота
	}

	if (userChar == 'X') i.botChar = '0';
	else i.botChar = 'X';
	i.userChar = userChar;
	i.status = PLAY;

	return i;
}

void updateDisplay(const Game game) { //табличка
	system("CLS");
	cout << "    1   2   3\n";
	cout << "  -------------\n";
	for (int i = 0; i < 3; i++) {
		cout << i + 1 << " | ";
		for (int j = 0; j < 3; j++) {
			cout << game.board[i][j] << " | ";
		}
		cout << "\n  -------------\n";
	}
}

void botTurn(Game* game) {
	int k = 0;
	int kBot = 0;
	int kUser = 0;

	for (int i = 0; i < 3; i++) {							// Проверка есть ли заполненные клетки, чтобы походить в центр
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == ' ') k++;
		}
	}
	if (k == 9) {
		game->board[1][1] = game->botChar;
		return;
	}
	k = 0;

	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) kUser++;
		else if (game->board[i][i] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][i] == ' ') {
				game->board[i][i] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][i] == ' ') {
				game->board[i][i] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == game->userChar) kUser++;
		else if (game->board[i][2 - i] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][2 - i] == ' ') {
				game->board[i][2 - i] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][2 - i] == ' ') {
				game->board[i][2 - i] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) kUser++;
		else if (game->board[i][i] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[0][i] == ' ') {
				game->board[0][i] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[0][i] == ' ') {
				game->board[0][i] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;

	for (int i = 0; i < 3; i++) {
		if (game->board[1][i] == game->userChar) kUser++;
		else if (game->board[1][i] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[1][i] == ' ') {
				game->board[1][i] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[1][i] == ' ') {
				game->board[1][i] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[2][i] == game->userChar) kUser++;
		else if (game->board[2][i] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[2][i] == ' ') {
				game->board[2][i] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[2][i] == ' ') {
				game->board[2][i] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[i][0] == game->userChar) kUser++;
		else if (game->board[i][0] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][0] == ' ') {
				game->board[i][0] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][0] == ' ') {
				game->board[i][0] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[i][1] == game->userChar) kUser++;
		else if (game->board[i][1] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][1] == ' ') {
				game->board[i][1] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][1] == ' ') {
				game->board[i][1] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;


	for (int i = 0; i < 3; i++) {
		if (game->board[i][2] == game->userChar) kUser++;
		else if (game->board[i][2] == game->botChar) kBot++;
	}
	if (kBot == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][2] == ' ') {
				game->board[i][2] = game->botChar;
				return;
			}
		}
	}
	else if (kUser == 2) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][2] == ' ') {
				game->board[i][2] = game->botChar;
				return;
			}
		}
	}
	kBot = 0;
	kUser = 0;

	srand(time(0));
	bool exit = false;
	while (!exit) {					// Если поставлен только один знак, то ход на рандом
		int x = rand() % 3;
		int y = rand() % 3;
		if (game->board[x][y] == ' ') {
			game->board[x][y] = game->botChar;
			exit = true;
			return;
		}
	}
}


void userTurn(Game* game) {
	int x, y; // х- столбцы. у- строки 
	cout << "Ход пользователя: ";
	cin >> x >> y;
	while (x > 3 || y < 1 || x < 1 || y > 3 || game->board[x - 1][y - 1] != ' ') {
		cout << "Неверные координаты" << endl;
		cout << "Ход пользователя: " << endl;
		cin >> x >> y;
	}
	game->board[x - 1][y - 1] = game->userChar;
}


void pobeda(Game* game, int kBot, int kUser) {
	if (kBot == 3) {
		game->status = BOT_WIN;
	}
	else if (kUser == 3) {
		game->status = USER_WIN;
	}
}

bool updateGame(Game* game) {
	int kBot = 0;
	int kUser = 0;
	for (int i = 0; i < 3; i++) {
		kBot = kUser = 0;
		for (int a = 0; a < 3; a++) {
			if (game->board[i][a] == game->userChar) kUser++;
			else if (game->board[i][a] == game->botChar) kBot++;
		}
		pobeda(game, kBot, kUser);
	}

	for (int i = 0; i < 3; i++) {
		kBot = kUser = 0;
		for (int a = 0; a < 3; a++) {
			if (game->board[a][i] == game->userChar) kUser++;
			else if (game->board[a][i] == game->botChar) kBot++;
		}
		pobeda(game, kBot, kUser);
	}
	kBot = kUser = 0;

	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) kUser++;
		else if (game->board[i][i] == game->botChar) kBot++;
	}
	pobeda(game, kBot, kUser);
	kBot = kUser = 0;

	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == game->userChar) kUser++;
		else if (game->board[i][2 - i] == game->botChar) kBot++;
	}
	pobeda(game, kBot, kUser);
	kBot = kUser = 0;

	int kSeg = 0;
	if (game->status == PLAY) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (game->board[i][j] == ' ') kSeg++;
			}
		}
		if (!kSeg) {
			game->status = NOT_WIN;
			return true;
		}
		game->isUserTurn = !game->isUserTurn;
		return false;
	}
	return true;
}