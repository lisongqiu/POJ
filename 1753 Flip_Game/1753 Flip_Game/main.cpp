#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

#define MAXN 5

int map[MAXN][MAXN];
int map_try[MAXN][MAXN];
int dirs[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };


void flip(int r, int c) {
	map_try[r][c] = 1 - map_try[r][c];
	for (int i = 0; i < 4; i++) {
		int rn = r + dirs[i][0];
		int cn = c + dirs[i][1];
		if (rn >= 0 && cn >= 0 && rn < 4 && cn < 4) {
			map_try[rn][cn] = 1 - map_try[rn][cn];
		}
	}
	return;
}

int flipTry(int flag) {
	int res = 0x3f3f3f3f;
	for (int i = 0; i <= 15; i++) {
		int cnt = 0;
		memcpy(map_try, map, sizeof(map));
		for (int j = 0; j < 4; j++) {
			if ((i >> j) % 2) {
				cnt++;
				flip(0, j);
			}
		}
		for (int r = 1; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				if (map_try[r - 1][c] != flag) {
					cnt++;
					flip(r, c);
				}
			}
		}
		bool isOk = true;
		for (int c = 0; c < 4; c++) {
			if (map_try[3][c] != flag) {
				isOk = false;
				break;
			}
		}
		if (isOk)
			res = min<int>(res, cnt);
	}
	return res;
}

int main() {
	string inp;
	for (int i = 0; i < 4; i++) {
		cin >> inp;
		for (int j = 0; j < 4; j++)
			map[i][j] = (inp[j] == 'b');
	}
	int res = min(flipTry(1), flipTry(0));
	if (res != 0x3f3f3f3f)
		cout << res << endl;
	else
		cout << "Impossible" << endl;
	system("pause");
	return 0;
}
