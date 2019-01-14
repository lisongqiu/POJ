#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 110

int N;
int a[MAXN];
int dp[MAXN][MAXN];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> a[i];
	for (int k = 1; k <= N - 1; k++) {
		for (int i = 0; i <= N - 1 - k; i++) {
			if (k == 1)
				dp[i][i + k] = 0;
			else if (k == 2)
				dp[i][i + k] = a[i] * a[i + 1] * a[i + 2];
			else {
				int minVal = INF;
				for (int j = i + 1; j <= i + k - 1; j++)
					minVal = min(minVal, dp[i][j] + dp[j][i + k] + a[i] * a[j] * a[i + k]);
				dp[i][i + k] = minVal;
			}
		}
	}
	cout << dp[0][N - 1] << endl;
	system("pause");
	return 0;
}