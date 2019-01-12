#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<string.h>

using namespace std;

#define MAXN 9

int N, K;
int m[MAXN][MAXN];
// int rows[MAXN];
int cols[MAXN];

int ds(int l, int r) {
	if (r == 0)
		return 1;
	if (l >= N)
		return 0;
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (cols[i] && m[l][i]) {
			cols[i] = false;
			cnt += ds(l + 1, r - 1);
			cols[i] = true;
		}
	}
	return cnt + ds(l + 1, r);
}

int main() {
	string line;
	while (cin >> N >> K) {
		if (N == -1 && K == -1)
			break;
		memset(m, 1, sizeof(m));
		memset(cols, 1, sizeof(cols));
		for (int i = 0; i < N; i++) {
			cin >> line;
			for (int j = 0; j < N; j++) {
				if (line[j] == '#')
					continue;
				m[i][j] = false;
			}	
		}
		cout << ds(0, K) << endl;
	}
	system("pause");
	return 0;
}