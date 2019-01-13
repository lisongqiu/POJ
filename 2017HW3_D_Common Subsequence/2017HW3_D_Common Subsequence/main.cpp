#define _CRT_SECURE_NO_DEPRECATE

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<string.h>

using namespace std;

#define MAXN 1010

string S1, S2;
int dp[MAXN][MAXN];

int main() {
	while (cin >> S1 >> S2) {
		for (int i = 0; i <= S1.size(); i++)
			dp[i][0] = 0;
		for (int i = 0; i <= S2.size(); i++)
			dp[0][i] = 0;
		for (int i = 1; i <= S1.size(); i++) {
			for (int j = 1; j <= S2.size(); j++) {
				if (S1[i - 1] == S2[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		cout << dp[S1.size()][S2.size()] << endl;
	}
	system("pause");
	return 0;
}