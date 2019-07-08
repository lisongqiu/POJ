#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

int main() {
	double inp;
	while (cin >> inp) {
		if (inp == 0.00)
			break;
		int res = 0;
		double cnt = 0.0;
		while (cnt < inp) {
			res++;
			cnt += 1.0 / (res + 1);
		}
		cout << res << " card(s)" << endl;
	}
		
	system("pause");
	return 0;
}
