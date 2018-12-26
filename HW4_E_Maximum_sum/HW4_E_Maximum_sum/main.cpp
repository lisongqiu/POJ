#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 50010
#define MAXM 10010

int T;
int N;
int a[MAXN];
int fdp[MAXN];
int bdp[MAXN];
int fdp2[MAXN];
int bdp2[MAXN];

int DP() {
	fdp[0] = a[0];
	for (int i = 1; i < N; i++) {
		fdp[i] = max(a[i], fdp[i - 1] + a[i]);
	}
	bdp[N - 1] = a[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		bdp[i] = max(a[i], bdp[i + 1] + a[i]);
	}
	fdp2[0] = fdp[0];
	for (int i = 1; i < N; i++)
		fdp2[i] = max(fdp2[i - 1], fdp[i]);
	bdp2[N - 1] = bdp[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		bdp2[i] = max(bdp[i], bdp2[i + 1]);
	}
	int res = -INF;
	for (int i = 0; i <= N - 2; i++) {
		res = max(res, fdp2[i] + bdp2[i + 1]);
	}
	return res;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		cout << DP() << endl;
	}
	system("pause");
	return 0;
}