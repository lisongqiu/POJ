#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

map<string, int> Haab = { {"pop", 0}, {"no", 1}, {"zip", 2}, {"zotz", 3}, {"tzec", 4}, {"xul", 5},{"yoxkin", 6},{"mol", 7},{"chen", 8},{"yax", 9},
					{"zac", 10},{"ceh", 11}, {"mac", 12},{"kankin", 13},{"muan", 14},{"pax", 15},{"koyab", 16},{"cumhu", 17},{"uayet", 18 } };
string Tzolkin[20] = { "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok",
					"chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau" };

int mod(int a, int m) {
	int res = a % m;
	if (res == 0)
		res = m;
	return res;
}

int main() {
	int N;
	scanf("%d", &N);
	printf("%d\n", N);
	while (N--) {
		int day, year;
		char tmp[20];
		scanf("%d. %s %d", &day, &tmp, &year);
		string month = string(tmp);
		int total = day + 1 + Haab[month] * 20 + year * 365;
		int res_days = mod(total, 260);
		int new_year = (total - res_days) / 260;
		int new_month = mod(res_days, 20);
		new_month -= 1;
		int new_day = mod(res_days, 13);
		cout << new_day << " " << Tzolkin[new_month] << " " << new_year << endl;
	}
	system("pause");
	return 0;
}
