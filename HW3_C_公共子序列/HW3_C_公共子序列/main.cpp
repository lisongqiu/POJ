#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>

using namespace std;

#define MAXN 201
int dp[MAXN][MAXN];

int main() {
	string a, b;
	while (cin >> a >> b) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < a.length(); i++) {
			for (int j = 0; j < b.length(); j++) {
				if (a[i] == b[j]) {
					if (i == 0 || j == 0)
						dp[i][j] = 1;
					else
						dp[i][j] = max(dp[i - 1][j - 1] + 1, dp[i][j]);
				}
				if (i >= 1)
					dp[i][j] = max(dp[i - 1][j], dp[i][j]);
				if (j >= 1)
					dp[i][j] = max(dp[i][j - 1], dp[i][j]);
			}
		}
		cout << dp[a.length() - 1][b.length() - 1] << endl;
	}
	system("pause");
	return 0;
}