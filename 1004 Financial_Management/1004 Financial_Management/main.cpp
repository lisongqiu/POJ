#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

double res = 0.0;

int main() {
	double inp;
	for (int i = 0; i < 12; i++) {
		cin >> inp;
		res += inp;
	}
	cout << "$" << res / 12 << endl;
	system("pause");
	return 0;
}