#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 110

int N;
long long maps[MAXN][MAXN];
bool used[MAXN];
long long sumL = 0;

int main() {
	while (cin >> N) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> maps[i][j];
		memset(used, 0, sizeof(used));
		used[0] = 1;
		sumL = 0;
		int res = N - 1;
		while (res--) {
			long long minL = INF, minI = -1, minJ = -1;
			for (int i = 0; i < N; i++) {
				if (!used[i])
					continue;
				for (int j = 0; j < N; j++) {
					if (used[j])
						continue;
					if (maps[i][j] < minL) {
						minL = maps[i][j];
						minI = i, minJ = j;
					}
				}
			}
			used[minJ] = true;
			sumL += minL;
		}
		cout << sumL << endl;
	}
	system("pause");
	return 0;
}