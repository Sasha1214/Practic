#include <iostream>

int main()
{
	double a, b, c;
	std::cin >> a >> b;
	c = a;
	a = b;
	b = c;
	cout << a << "\t" << b << "\n";
	b = b + a;
	a = b - a;
	b = b - a;
	cout << a << "\t" << b << "\n";
}