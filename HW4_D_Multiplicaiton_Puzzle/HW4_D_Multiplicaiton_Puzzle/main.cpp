#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 110

int N;
int dp[MAXN][MAXN];
int a[MAXN];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> a[i];
	for (int k = 2; k <= N - 1; k++) {
		for (int i = 0; i <= N - 1 - k; i++) {
			if (k == 2)
				dp[i][i + k] = a[i] * a[i + 1] * a[i + 2];
			else {
				int minVal = a[i] * a[i + 1] * a[i + k] + dp[i + 1][i + k];
				minVal = min(minVal, a[i] * a[i + k - 1] * a[i + k] + dp[i][i + k - 1]);
				for (int j = i + 2; j <= i + k - 2; j++) {
					minVal = min(minVal, a[i] * a[j] * a[i + k] + dp[i][j] + dp[j][i + k]);
				}
				dp[i][i + k] = minVal;
			}
		}
	}
	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}*/
	cout << dp[0][N - 1] << endl;
	system("pause");
	return 0;
}