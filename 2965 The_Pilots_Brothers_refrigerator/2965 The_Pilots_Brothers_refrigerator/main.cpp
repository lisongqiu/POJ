#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>

using namespace std;

#define INF 0x3f3f3f3f
int m[4][4];
bool used[4][4];
bool currents[4][4];
int res;

void flip(int r, int c) {
	for (int i = 0; i < 4; i++)
		m[r][i] = 1 - m[r][i];
	for (int i = 0; i < 4; i++) {
		if (i == r)
			continue;
		m[i][c] = 1 - m[i][c];
	}
	return;
}

int dfs(int idx, int cnt) {
	if (idx > 15) {
		// check.
		bool isTrue = true;
		for (int r = 0; r < 4; r++)
			for (int c = 0; c < 4; c++)
				if (!m[r][c])
					isTrue = false;
		if (isTrue) {
			if (cnt > res) {
				res = cnt;
				memcpy(used, currents, sizeof(currents));
			}
			return cnt;
		}
		else
			return INF;
	}
	int c = idx % 4;
	int r = (idx - c) / 4;
	// flip.
	flip(r, c);
	currents[r][c] = true;
	int rnt1 = dfs(idx + 1, cnt + 1);
	flip(r, c);
	currents[r][c] = false;
	// not flip.
	int rnt2 = dfs(idx + 1, cnt);
	int rnt = min(rnt1, rnt2);
	return rnt;
}

int main() {
	string inp;
	for (int i = 0; i < 4; i++) {
		cin >> inp;
		for (int j = 0; j < 4; j++)
			m[i][j] = (inp[j] == '-');
	}
	memset(currents, 0, sizeof(currents));
	memset(used, 0, sizeof(used));
	cout << dfs(0, 0) << endl;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++)
			if (used[r][c])
				cout << r + 1 << " " << c + 1 << endl;
	}
	system("pause");
	return 0;
}

/*
-+--
----
----
-+--
*/