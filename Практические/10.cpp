#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	double z, ot = 1;
	int pow;
	cin >> z >> pow;
	int pow_2 = pow;
	while (pow_2 != 0)
	{
		ot = ot * z;
		pow_2 = abs(pow_2) - 1;
	}

	if (pow > 0) {
		cout << "Ответ: " << ot;
	}
	else if (pow < 0 && z == 0) {
		cout << "Нет решений";
	}
	else if (pow < 0) {
		ot = 1 / ot;
		cout << "Ответ: " << ot;
	}
	else if (pow == 0) {
		cout << "Ответ: " << ot;
	}
}
