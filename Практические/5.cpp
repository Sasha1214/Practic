#include <iostream>

int main()
{
	double x0, u0, t, a;
	a = -9.8;
	cin >> x0 >> u0 >> t;
	cout << x0 + u0 * t + a * t * t / 2;
}
}