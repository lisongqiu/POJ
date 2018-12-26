#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>

using namespace std;

#define MAXN 100010
int T, N;
int a[MAXN];
int fdp[MAXN];
int bdp[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		//compute res.
		for (int i = N - 1; i > 0; i--)
			a[i] = a[i] - a[i - 1];
		//init.
		memset(fdp, 0, sizeof(fdp));
		memset(bdp, 0, sizeof(bdp));
		//dp.
		for (int i = 1; i <= N - 1; i++)
			fdp[i] = max(fdp[i - 1] + a[i], a[i]);
		for (int i = 1; i <= N - 1; i++)
			fdp[i] = max(fdp[i], fdp[i - 1]);
		for (int i = N - 1; i >= 1; i--)
			bdp[i] = max(bdp[i + 1] + a[i], a[i]);
		for (int i = N - 1; i >= 1; i--)
			bdp[i] = max(bdp[i], bdp[i + 1]);
		//search.
		int rnt = -0x3f3f3f3f;
		for (int i = 1; i <= N - 1; i++) {
			rnt = max(rnt, fdp[i] + bdp[i + 1]);
		}
		printf("%d\n", rnt);
	}
	system("pause");
	return 0;
}