#include <iostream>

int main()
{
	setlocale(LC_ALL, "Rus");
	double a, b;
	char x;
	cout << "a (+,-,/,*) b\n";
	cin >> a >> x >> b;
	cout << "=";
	switch (x)
	{
	case('+'):
	{
		cout << a + b;
		break;
	}
	case('-'):
	{
		cout << a - b;
		break;
	}
	case('*'):
	{
		cout << a * b;
		break;
	}
	case('/'):
	{
		cout << a / b;
		break;
	}
	default:
	{
		cout << "\bНеверный знак операции\n";
		break;
	}
	}

}