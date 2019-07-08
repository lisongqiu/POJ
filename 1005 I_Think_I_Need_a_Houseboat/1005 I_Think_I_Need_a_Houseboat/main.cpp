#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <math.h>

using namespace std;

#define pi 3.1415926
int N;

int main() {
	double x, y;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> x >> y;
		double area = pi * (x * x + y * y) / 2;
		cout << "Property " << i << ": This property will begin eroding in year " << ceil(area / 50.0) << "." << endl;
	}
	cout << "END OF OUTPUT." << endl;
	system("pause");
	return 0;
}