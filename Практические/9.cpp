int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int b, c, i, a;
	c = 1;

	while (c == 1)
	{
		i = 0;
		a = rand() % 101;
		cout << "Игра угадай число:\n";
		while (i < 5)
		{
			cin >> b;
			if (b > a)
			{
				cout << "Загаданное число меньше " << b << "\n";
			}
			else if (b < a)
			{
				cout << "Загаданное число больше " << b << "\n";
			}
			else if (b = a)
			{
				cout << "Поздравляю! Вы угадали!\n";
				break;
			}
			i++;
		}
		if (i == 5)
		{
			cout << "Вы проиграли. Было загадано: " << a;
		}
		cout << "\nХотите начать сначала? (1-Да)\n";
		cin >> c;
	}
}