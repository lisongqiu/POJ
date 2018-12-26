#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 1010

int getIdx(int x, int y) {
	return x * MAXN + y;
}

int map[MAXN*MAXN];
int par[MAXN*MAXN];
int T;
int N, M;
int beginIdx, endIdx;
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int getPar(int a) {
	if (par[a] == a)
		return a;
	int pa = getPar(par[a]);
	par[a] = pa;
	return par[a];
}

void merge(int a, int b) {
	int pa = getPar(a);
	int pb = getPar(b);
	if (pa == pb)
		return;
	par[pa] = pb;
	return;
}

void expand(int a, int b) {
	int ci = getIdx(a, b);
	for (int i = 0; i < 4; i++) {
		int tx = a + dir[i][0];
		int ty = b + dir[i][1];
		int ti = getIdx(tx, ty);
		if (tx >= 1 && tx <= N && ty >= 1 && ty <= N && map[ti]) {
			if (getPar(ci) == getPar(ti))
				continue;
			merge(ci, ti);
		}
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		//init.
		memset(map, 0, sizeof(map));
		for(int i=1;i<=N;i++)
			for (int j = 1; j <= N; j++) {
				int idx = getIdx(i, j);
				par[idx] = idx;
			}
		beginIdx = -1;
		endIdx = -1;
		int a, b;
		int res = -1;
		for (int i = 1; i <= M; i++) {
			scanf("%d%d", &a, &b);
			if (res != -1)
				continue;
			int idx = getIdx(a, b);
			map[idx] = 1;
			if (a == 1) {
				if (beginIdx == -1)
					beginIdx = idx;
				else
					merge(beginIdx, idx);
			}
			if (a == N) {
				if (endIdx == -1)
					endIdx = idx;
				else
					merge(endIdx, idx);
			}
			expand(a, b);
			if (beginIdx != -1 && endIdx != -1 && getPar(beginIdx)==getPar(endIdx))
				res = i;
		}
		printf("%d\n", res);
	}
	system("pause");
	return 0;
}
