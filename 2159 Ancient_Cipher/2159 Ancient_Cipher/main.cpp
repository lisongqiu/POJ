#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

int s1[26], s2[26];

int main() {
	memset(s1, 0, sizeof(s1));
	memset(s2, 0, sizeof(s2));

	string a, b;
	cin >> a >> b;
	if (a.length() != b.length())
		cout << "NO" << endl;
	else {
		for (int i = 0; i < a.length(); i++) {
			s1[a[i] - 'A']++;
			s2[b[i] - 'A']++;
		}
		sort(s1, s1 + 26);
		sort(s2, s2 + 26);
		bool isTrue = true;
		for (int i = 0; i < 26; i++) {
			if (s1[i] != s2[i]) {
				isTrue = false;
				break;
			}
		}
		if (isTrue)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	system("pause");
	return 0;
}