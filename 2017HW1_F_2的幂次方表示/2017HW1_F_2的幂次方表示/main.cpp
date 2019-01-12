#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void func(int n) {
	if (n == 0)
		return;
	if (n == 1) {
		cout << "2(0)";
		return;
	}
	if (n == 2) {
		cout << 2;
		return;
	}
	int power = 0;
	while (pow(2, power) <= n)
		power++;
	power--;
	// cout << power << endl;
	if (pow(2, power) == n) {
		if (power == 1)
			cout << 2;
		else {
			cout << "2(";
			func(power);
			cout << ")";
		}
	}
	else {
		if (power == 1) {
			cout << 2;
			cout << "+";
		}
		else {
			cout << "2(";
			func(power);
			cout << ")+";
		}
		func(n - pow(2, power));
	}
}

int main() {
	int n;
	cin >> n;
	func(n);
	cout << endl;
	system("pause");
	return 0;
}
