#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

int main() {
	string inp;
	while (getline(cin, inp)) {
		if (inp == "#")
			break;
		int rnt = 0;
		for (int i = 0; i < inp.size(); i++) {
			if (inp[i] == ' ')
				continue;
			rnt += (i + 1)*(inp[i] - 'A' + 1);
		}
		cout << rnt << endl;
	}
	system("pause");
	return 0;
}