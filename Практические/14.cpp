int main()
{
	setlocale(LC_ALL, "rus");
	int s, l1, r1, l2, r2, k;
	cin >> s >> l1 >> r1 >> l2 >> r2;

	if (l1 + l2 > s || r2 + r1 < s)
		cout << "-1" << endl;
	else {
		for (int i = l1; i <= r1; i++) {
			for (int j = l2; j <= r2; j++) {
				if (i + j == s) {
					cout << i << " " << j << endl;
					return 0;

				}
			}
		}
	}
}