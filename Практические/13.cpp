int main() {
	int n, x = 1, k = 0;
	cin >> n;
	while (x <= n) {
		x *= 2;
		k++;
	}
	cout << k;
}