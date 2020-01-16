
#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	double a, b, c, D, x1, x2;
	cin >> a >> b >> c;
	if (a == 0) {
		cout << "x = -1";
	}
	else {
		D = b * b - 4 * a * c;




		if (D < 0) {
			cout << "Нет действительных корей";
		}
		else if (D == 0) {
			x1 = -b / (2 * a);
			cout << x1;
		}
		else {
			x1 = (-b + sqrt(D)) / (2 * a);
			x2 = (-b - sqrt(D)) / (2 * a);

			cout << "x1 = " << x1 << endl;
			cout << "x2 = " << x2 << endl;


		}

	}



}