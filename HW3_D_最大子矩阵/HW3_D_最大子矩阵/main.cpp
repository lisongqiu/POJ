#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

#define MAXN 101

int N;
int mat[MAXN][MAXN];
int tmp[MAXN];
int dp[MAXN];
int rnt = -0x3f3f3f3f;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> mat[i][j];
	for (int i = 0; i < N; i++) {
		memset(tmp, 0, sizeof(tmp));
		for (int j = i; j < N; j++) {
			for (int k = 0; k < N; k++) {
				dp[k] = -0x3f3f3f3f;
				tmp[k] += mat[j][k];
			}
			dp[0] = tmp[0];
			rnt = max(dp[0], rnt);
			for (int k = 1; k < N; k++) {
				dp[k] = max(dp[k - 1] + tmp[k], tmp[k]);
				rnt = max(dp[k], rnt);
			}
		}
	}
	cout << rnt << endl;
	system("pause");
	return 0;
}