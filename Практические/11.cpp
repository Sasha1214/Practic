#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int z, ot = 1;
	cin >> z;
	for (int i = 1; i <= z; i++)
	{
		ot = ot * i;
	}
	cout << "Ответ: " << ot;



}