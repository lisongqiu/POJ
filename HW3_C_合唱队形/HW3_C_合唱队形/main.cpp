#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 101
int N;
int a[MAXN];
int dp[MAXN][2];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		dp[i][0] = 1;
		dp[i][1] = 1;
		for (int j = 1; j < i; j++) {
			if (a[i] > a[j])
				dp[i][0] = max(dp[i][0], dp[j][0] + 1);
			else if (a[i] < a[j]) {
				dp[i][1] = max(dp[i][1], dp[j][1] + 1);
				dp[i][1] = max(dp[i][1], dp[j][0] + 1);
			}
		}
		dp[i][1] = max(dp[i][0], dp[i][1]);
	}
	//for (int i = 1; i <= N; i++)
	//	cout << dp[i][0] << " " << dp[i][1] << endl;
	int res = 0x3f3f3f3f;
	for (int i = 1; i <= N; i++)
		res = min(res, N - dp[i][1]);
	printf("%d\n", res);
	system("pause");
	return 0;
}