#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>

using namespace std;

map<string, int> Haab;

string Tzolkin[20] = { "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok",
					"chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau" };

int mod(int a, int m) {
	int res = a % m;
	if (res == 0)
		res = m;
	return res;
}

int main() {
	Haab.insert(pair<string, int>("pop", 0));
	Haab.insert(pair<string, int>("no", 1));
	Haab.insert(pair<string, int>("zip", 2));
	Haab.insert(pair<string, int>("zotz", 3));
	Haab.insert(pair<string, int>("tzec", 4));
	Haab.insert(pair<string, int>("xul", 5));
	Haab.insert(pair<string, int>("yoxkin", 6));
	Haab.insert(pair<string, int>("mol", 7));
	Haab.insert(pair<string, int>("chen", 8));
	Haab.insert(pair<string, int>("yax", 9));
	Haab.insert(pair<string, int>("zac", 10));
	Haab.insert(pair<string, int>("ceh", 11));
	Haab.insert(pair<string, int>("mac", 12));
	Haab.insert(pair<string, int>("kankin", 13));
	Haab.insert(pair<string, int>("muan", 14));
	Haab.insert(pair<string, int>("pax", 15));
	Haab.insert(pair<string, int>("koyab", 16));
	Haab.insert(pair<string, int>("cumhu", 17));
	Haab.insert(pair<string, int>("uayet", 18));
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
