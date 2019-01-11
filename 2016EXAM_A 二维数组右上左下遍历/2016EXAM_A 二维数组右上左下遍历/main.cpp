#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 110

int a[MAXN][MAXN];
bool used[MAXN][MAXN];

int main() {
	int r, c;
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> a[i][j];
	for (int i = 0; i < c; i++) {
		int cr = 0, cc = i;
		while (cr <= r - 1 && cc >= 0) {
			cout << a[cr][cc] << endl;
			used[cr][cc] = true;
			cr++;
			cc--;
		}
	}
	for (int j = 0; j <= r - 1; j++) {
		int cr = j, cc = c - 1;
		if (used[cr][cc])
			continue;
		while (cr <= r - 1 && cc >= 0) {
			cout << a[cr][cc] << endl;
			cr++;
			cc--;
		}
	}
	system("pause");
	return 0;
}
