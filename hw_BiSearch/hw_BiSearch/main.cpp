#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

long long f(long long n) {
	long long res = n * log2(n);
	return res;
}

int main() {
	long long M = 3600 * pow(10, 10);
	long long l = 0, r = M;
	while (l < r) {
		long long mid = (r + l) / 2;
		cout << "mid: " << mid << endl;
		if (f(mid) < M)
			l = mid + 1;
		else
			r = mid - 1;
	}
	cout << "res: " << l << endl;
	cout << "f: " << f(l) << endl;
	cout << "f(l+1): " << f(l + 1) << endl;
	system("pause");
	return 0;
}