#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 101

int v[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
	int F, V;
	scanf("%d%d", &F, &V);
	for (int i = 1; i <= F; i++)
		for (int j = 1; j <= V; j++)
			scanf("%d", &v[i][j]);
	// init.
	for (int i = 0; i <= V; i++)
		dp[0][i] = 0;
	for (int i = 1; i <= F; i++)
		dp[i][0] = 0;
	for (int i = 1; i <= F; i++) {
		for (int j = 1; j <= V; j++) {
			int max_val = -INF;
			for (int k = i; k <= j; k++)
				max_val = max(max_val, dp[i - 1][k - 1] + v[i][k]);
			dp[i][j] = max_val;
		}
	}
	cout << dp[F][V] << endl;
	system("pause");
	return 0;
}