МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РАССИЙСКОЙ ФЕДЕРАЦИИ
Федеральное государственное автономное образовательное учреждение высшего образования"
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им.Вернадского"
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ 
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе № 4 <br/> по дисциплине "Программирование"
<br/>

студента первого курса ПИ-б-о-191(1)
Мирончук Александры Алексеевны
направления подготовки 09.03.04 "Программная инженерия"
<br/>

<table>
<tr><td>Научный руководитель<br/>старший преподователь кафедры<br/>компьютерой инженерии и моделирования<br/>
<td/>(оценка)<td/>
<td/>Чабанов В.В.<td/>
</tr>
</table>
<br/><br/>

Симферополь,2020

***
### Тема: Иксики-нолики

#### Цель: 
**Закрепить навыки работы с перечислениями;*

**Закрепить навыки работы с структурами;*

**Освоить методы составления многофайловых программ.*

Для реализации программы были созданы вспомогательный и заголовочный файл, которые предтавлены ниже в отчете.


![Рисунок 1]( https://sun9-45.userapi.com/c857032/v857032230/16dc20/RVvRfTRa2Ko.jpg)

(Рис.1 Все файлы для создания проекта)



### Основной файл, реализующий игру (Laba4.cpp): 

```cpp
#include <iostream>
#include "XO.h"
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	char simvol=' ';
	while (simvol != 'X' && simvol != '0') {
		cout << "Введите символ: " << endl;
		cin >> simvol;
	}
	Game pop = initGame(simvol);
	while (!updateGame(&pop)) {
		if (pop.isUserTurn) userTurn(&pop);
		else botTurn(&pop);
		updateDisplay(pop);
	}
	if (pop.status == USER_WIN) {
		cout << "Пользователь выиграл";
	}
	else if (pop.status == BOT_WIN) {
		cout << "Бот выиграл";
	}
	else {
		cout << "Ничья";
	}
}

```

### Заголовочный файл X0.h(связывает главный и вспомогательный):

```cpp
#pragma once

/* Состояния игры */
enum Status {
	PLAY,            // Игра продолжается
	USER_WIN,        // Игрок победил
	BOT_WIN,         // Бот победил
	NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};
struct Game {
	char board[3][3];  // Игровое поле
	bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
	char userChar;    // Символ которым играет пользователь
	char botChar;     // Символ которым играет бот
	Status status;
};

/**
* Выполняет следующие действия:
*  1. Очищает игровое поле заполняя его пробелами
*  2. Случайным образом определяет чей ход
*  3. Устанавливает символ для Игрока (Задаётся параметром userChar)
*  4. Устанавливает символ для бота
*  5. Возвращает заполненную структуру
*/
Game initGame(char userChar);
/**
* Выполняет следующие действия:
*  1. Очищает экран
*  2. Отображает содержимое игрового поля. Например так (можно по своему):
*         a   b   c
*       -------------
*     1 | O | O | X |
*       -------------
*     2 |   |   |   |
*       -------------
*     3 |   |   | X |
*       -------------
*/
void updateDisplay(const Game game);
/**
* Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
* Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ. Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
*/
void botTurn(Game* game);
/**
* Функция отвечает за ход игрока. Если игрок вводит не допустимые
* значения, ругнуться и попросить ввести заново
*/
void userTurn(Game* game);
/**
* Функция определяет как изменилось состояние игры после последнего хода.
* Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
* игроку.
* Функция возвращает true, если есть победитель или ничья, иначе false.
*/
bool updateGame(Game* game);
```

### Вспомогательный файл X0.cpp (основные функции игры): 

```cpp
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

	for (int i = 0; i < 3; i++) {						
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
	while (!exit) {				
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
```


![Рисунок 1](https://sun9-51.userapi.com/c857032/v857032230/16dc78/JsxriYxfxvc.jpg)

(Рис.2 Победа над машиной)

***

#### Вывод: в ходе лаборатоной работы я освоила методы составления многофайловых программ, закрепиа навыки работы с перечислениями и струкрурами.
