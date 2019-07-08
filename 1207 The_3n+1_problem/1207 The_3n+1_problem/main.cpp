#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

int a, b;

long long f(int n) {
	long long rnt = 1;
	while (n != 1) {
		rnt++;
		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
	}
	return rnt;
}

int main() {
	while (cin >> a >> b) {
		long long res = 0;
		int aa = min(a, b), bb = max(a, b);
		for (int i = aa; i <= bb; i++)
			res = max(res, f(i));
		cout << a << " " << b << " " << res << endl;
	}
	system("pause");
	return 0;
}
