#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 1010

int X, N, T;
int C[MAXN][MAXN];

void add(int x, int y, int v) {
	for (int i = x; i <= N; i += i & (-i))
		for (int j = y; j <= N; j += j & (-j))
			C[i][j] += v;
	return;
}

int query(int x, int y) {
	int rnt = 0;
	for (int i = x; i > 0; i -= i & (-i))
		for (int j = y; j > 0; j -= j & (-j))
			rnt += C[i][j];
	return rnt;
}

int main() {
	scanf("%d", &X);
	while (X--) {
		memset(C, 0, sizeof(C));
		scanf("%d%d", &N, &T);
		char op;
		int x1, y1, x2, y2;
		while (T--) {
			scanf(" %c", &op);
			if (op == 'C') {
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				add(x1, y1, 1);
				add(x1, y2 + 1, 1);
				add(x2 + 1, y1, 1);
				add(x2 + 1, y2 + 1, 1);
			}
			else {
				scanf("%d%d", &x1, &y1);
				printf("%d\n", query(x1, y1) % 2);
			}
		}
		printf("\n");
	}
	system("pause");
	return 0;
}