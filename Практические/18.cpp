int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	int SIZE = 20;
	double arr[20];
	double MIN, MAX;
	for (int i = 0; i < SIZE; i++) {
		arr[i] = -100 + rand() % 201;
	}
	MIN = arr[0];
	MAX = arr[0];
	for (int i = 0; i < SIZE; i++) {
		if (arr[i] < MIN) MIN = arr[i];
		if (arr[i] > MAX) MAX = arr[i];
		cout << arr[i] << " "; ;
	}
	cout << endl;
	cout << MIN << endl;
	cout << MAX;
}