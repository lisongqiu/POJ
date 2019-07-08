#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;

double getH(double t, double d) {
	double e = 6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (d + 273.16)));
	double h = 0.5555*(e - 10.0);
	return t + h;
}

double getD(double t, double h) {
	double hh = h - t;
	double e = hh / 0.5555 + 10.0;
	double d = 1 / (1 / 273.16 - log(e / 6.11) / 5417.7530) - 273.16;
	return d;
}

double getT(double d, double h) {
	double e = 6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (d + 273.16)));
	double hh = 0.5555*(e - 10.0);
	return h - hh;
}

int main() {
	string p1, p2;
	double a, b;
	double t, d, h;
	while (cin >> p1) {
		if (p1 == "E")
			break;
		cin >> a >> p2 >> b;
		if (p1 == "T" && p2 == "D") {
			t = a, d = b;
			h = getH(t, d);
		}
		else if (p1 == "D" && p2 == "T") {
			d = a, t = b;
			h = getH(t, d);
		}
		else if (p1 == "T" && p2 == "H") {
			t = a, h = b;
			d = getD(t, h);
		}
		else if (p1 == "D" && p2 == "H") {
			d = a, h = b;
			t = getT(d, h);
		}
		else if (p1 == "H" && p2 == "T") {
			h = a, t = b;
			d = getD(t, h);
		}
		else if (p1 == "H" && p2 == "D") {
			h = a, d = b;
			t = getT(d, h);
		}
		cout << fixed << setprecision(1) << "T " << t << " D " << d << " H " << h << endl;
	}
	system("pause");
	return 0;
}