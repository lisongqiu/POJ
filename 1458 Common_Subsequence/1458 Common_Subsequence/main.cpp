#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>

using namespace std;

const int MAXN = 1001;
string a, b;
int dp[MAXN][MAXN];

int main() {
	while (cin >> a >> b) {
		for (int i = 0; i <= a.length(); i++)
			for (int j = 0; j <= b.length(); j++)
				dp[i][j] = 0;
		for (int i = 1; i <= a.length(); i++) {
			for (int j = 1; j <= b.length(); j++) {
				if (a[i - 1] == b[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
		cout << dp[a.length()][b.length()] << endl;
	}
	return 0;
}