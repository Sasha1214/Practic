double BMI(double weight, double height) {
	double b = weight / (height * height);
	return b;
}
// Принимает численное значение ИМТ и печатает на экран соответствующую категорию
void printBMI(double BMI) {
	setlocale(LC_ALL, "rus");
	if (BMI < 18.5)cout << "Недостаточная масса";
	else if (BMI > 18.5 && BMI < 25.0) cout << "Норма";
	else if (BMI > 25.0 && BMI < 30.0) cout << "Избыточная масса";
	else cout << "Ожирение";
}

int main() {
	double h, m;
	cin >> m >> h;
	h = h / 100;
	printBMI(BMI(m, h));
}