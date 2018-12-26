#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 101
#define INF 0x3f3f3f3f

int N;
int map[MAXN][MAXN];
int used[MAXN];
int minL[MAXN];

int main() {
	while (~scanf("%d", &N)) {
		memset(used, 0, sizeof(used));
		for (int i = 0; i < N; i++)
			minL[i] = INF;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		int res = 0;
		minL[0] = 0;
		for (int k = 0; k < N; k++) {
			int minIdx = 0;
			int minLen = INF;
			for (int i = 0; i < N; i++) {
				if (used[i])
					continue;
				if (minL[i] < minLen) {
					minIdx = i;
					minLen = minL[i];
				}
			}
			res += minLen;
			used[minIdx] = true;
			for (int i = 0; i < N; i++) {
				if (used[i])
					continue;
				minL[i] = min<int>(minL[i], map[minIdx][i]);
			}
		}
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}