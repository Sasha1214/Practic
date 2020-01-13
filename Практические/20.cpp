#include <iostream>
using namespace std;

void sort(double arr[], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void vivod(double arr[], int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
}

int main()
{
	int n;
	cin >> n;
	double* a = new double[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, n);
	vivod(a, n);
}
