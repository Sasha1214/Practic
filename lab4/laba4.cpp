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

