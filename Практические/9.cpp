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
		cout << "���� ������ �����:\n";
		while (i < 5)
		{
			cin >> b;
			if (b > a)
			{
				cout << "���������� ����� ������ " << b << "\n";
			}
			else if (b < a)
			{
				cout << "���������� ����� ������ " << b << "\n";
			}
			else if (b = a)
			{
				cout << "����������! �� �������!\n";
				break;
			}
			i++;
		}
		if (i == 5)
		{
			cout << "�� ���������. ���� ��������: " << a;
		}
		cout << "\n������ ������ �������? (1-��)\n";
		cin >> c;
	}
}