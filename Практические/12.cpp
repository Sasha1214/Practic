int main()
{
	setlocale(LC_ALL, "rus");
	int x;
	cin >> x;
	for (int i = 2; i < x; i++)
		if (x % i == 0) {
			cout << "���������\n";
		}
	cout << "�������\n";
}