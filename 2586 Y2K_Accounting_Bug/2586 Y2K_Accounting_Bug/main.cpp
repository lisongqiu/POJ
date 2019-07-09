#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

int s, d;
int months[12];

int main() {
	while (cin >> s >> d) {
		int cnt = 0;
		while (cnt*s < (5 - cnt)*d)
			cnt++;
		cnt--;
		for (int i = 0; i < cnt; i++)
			months[i] = s;
		for (int i = cnt; i < 5; i++)
			months[i] = -d;
		long long window = cnt * s - d * (5 - cnt);
		for (int i = 5; i < 12; i++) {
			window -= months[i - 5];
			if (window < -s)
				months[i] = s;
			else
				months[i] = -d;
			window += months[i];
		}
		long long rnt = 0;
		for (int i = 0; i < 12; i++)
			rnt += months[i];
		if (rnt > 0)
			cout << rnt << endl;
		else
			cout << "Deficit" << endl;
	}
	system("pause");
	return 0;
}
