#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, " rus");
	int spos; 
	double a, b, c, p, S;
	cout << "������� ����� (1 ��� 2) : " << endl;
	cin >> spos; 

	if (spos == 1) { 
		cout << "������� ������� ������������ (a, b, c) : " << endl;
		cin >> a >> b >> c;
		if ((a < b + c) && (a > b - c) && (b < a + c) && (b > a - c) && (c < a + b) && (c > a - b)) { 
			p = (a + b + c) / 2; 
			S = sqrt(p * (p - a) * (p - b) * (p - c));
			cout << " S = " < ;
		}
		else {
			cout << "������������ �� ����������";
		}
	}
	else if (spos == 2) { 
		double x1, x2, x3, y1, y2, y3; 
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		if ((a < b + c) && (a > b - c) && (b < a + c) && (b > a - c) && (c < a + b) && (c > a - b)) { 
			S = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2
			cout << " S = " < ;
		}
		else {
			cout << "������������ �� ����������";
		}
	}
	else cout << "������";
}